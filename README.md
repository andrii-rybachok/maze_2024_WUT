# Maze Solver

**Authors:** Chaienko O., Rybachok A.   
**Date:** March 7, 2024

## Project Goal

The goal of this project is to develop a C program that finds the shortest path from the entry to the exit in a given maze. The program is optimized to use as little memory as possible, with a maximum usage of 512kB during execution. It supports mazes up to a maximum size of 1024 × 1024 in terms of navigable paths.

## Features

The program offers the following functionalities:

- **Maze Generation (-g)**  
  Generates a maze with dimensions specified by the user. The dimensions are provided as a character vector containing numbers separated by a comma (first columns, then rows).

- **Maze Reading (-r)**  
  Reads a maze from a text file. The file must include the following symbols:
  - **P** – maze entry point
  - **K** – maze exit point
  - **X** – wall
  - **Space** – traversable path

- **Maze Saving (-w)**  
  Saves a generated maze to a text file. This function is used together with the maze generation feature (-g).

- **Maze Solving (-s)**  
  Finds the shortest path from the entry point "P" to the exit point "K" using Dijkstra's algorithm. The solution is saved to a specified file as a list of steps. An example output might look like:
