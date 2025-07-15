#include "TSP.hpp"

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}

/**
 * Constructs a tour using the nearest neighbor heuristic for the traveling salesperson problem (TSP).
 * Starting from the city of the given ID, it iteratively visits the nearest unvisited city and returns to the start.
 *
 * @param cities A list of `Node` objects representing the cities to be visited.
 * @param start_id The unique identifier of the starting city.
 * @return A `TSP::Tour` object representing the path, edge weights, and total distance of the computed tour.
 * 
 * @pre `start_id` must be a valid city ID within the range of IDs in `cities`.
 * @note The ith weight in `weights` is the distance traveled from the previous (i-1) city to the current i city (represented by the ith city in the returned Tour.path)
 *       As such, the first weight will ALWAYS equal 0, since there is no edge from the start city to itself
 *
 */
TSP::Tour TSP::nearestNeighbor(std::list<Node> cities, const size_t& start_id) {
  Tour result;

  auto start = cities.begin(); //Declare outside of iterator so it can be used in the future
  bool found = false; 
  //'start_id' must be a valid city ID within the range of IDs in 'cities'
  //Iterate through cities to check for valid one with start_id and set it as the starting city 
  for(start; start != cities.end(); ++start) {
    if(start->id == start_id) {
      found = true; 
      break;
    }
  }
  if(!found) {
    return result; //Returns nothing
  }

  //Add starting city to path and its distance (0) to weights & total distance
  result.path.push_back(*start); 
  result.weights.push_back(0); 
  result.total_distance = 0; 
  //Assign current node to starting city and delete to ensure we don't return until the end
  Node current = *start; 
  cities.erase(start); 

  while(!cities.empty()) { //Keep iterating until all remaining cities are visited
    auto next = cities.begin();
    int least = current.distance(*next); 
    //Iterate through unremaining unvisited cities to check which city is the closest 
    for(auto it = cities.begin(); it != cities.end(); ++it) {
      if(least > current.distance(*it)) { //Ensure that the distance is the least 
        next = it;
        least = current.distance(*it);
      }
    }

    //Add confirmed next closest city to path and its distance to weights
    result.path.push_back(*next);
    result.weights.push_back(least);
    result.total_distance += least;
    //Assign current node to next closest city and delete to ensure we don't return
    current = *next;
    cities.erase(next);
  }

  //Return to starting city 
  int detour = current.distance(result.path.front()); //exact distance from beginning to end (not including tour path)
  result.path.push_back(result.path.front());
  result.weights.push_back(detour);
  result.total_distance += detour; 
  return result;
}