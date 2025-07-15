### Project 3 - TSP Nearest Neighbor Algorithm ####

--- --- --- --- --- --- ---

### Overview ### 

This project approximates a solution for the Traveling Salesman Problem (TSP). Given a list of cities and distances, the algorithm attempts to construct a reasonably efficient tour by always visiting the nearest unvisited city.

The goal was to work with real geographical datasets, implement it efficiently in C++, and gain experience with algorithm design and graph traversal.

--- --- --- --- --- --- ---
   
### Requirements ### 

" For this assignment, you will implement the nearest neighbor heuristic for TSPs (we will cover this in class, and it's outlined in the slides).

The files provided will read the files from https://www.math.uwaterloo.ca/tsp/world/countries.html and time your solution.

You can download the file for countries to test your algorithm on from the link that says "data" in each country entry.

You will only need to modify TSP.cpp and perhaps TSP.hpp. You must implement the function Tour nearestNeighbor(std::list<Node> cities, const size_t& start_id = 1), whose prototype can be found in TSP.hpp. If you use helper functions, you must add them to TSP.hpp as well."
