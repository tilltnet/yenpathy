library(igraphdata)
library(igraph)
library(yenpathy)
data("UKfaculty")
k_shortest_paths(UKfaculty, 1, 2, 1000)

# Run this from console to check for memory leaks
# make sure valgrind is installed for this to work
# R -d "valgrind --leak-check=full" -e "source('tests/find_memory_leaks.r')"

