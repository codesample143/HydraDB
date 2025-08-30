## Overview
HydraDB is a miniature relational database fully written in C++. Primary focus is on implementing efficient reads and writes, storage handling, efficient query processing and optimization, and eventual integration with more modern database structures (VectorDB, GraphDB, TimeSeriesDB). Currently, the MVP can handle simple SQL and alter the B+ tree data structure accordingly. 

## Diagram
<img width="3024" height="1490" alt="image" src="https://github.com/user-attachments/assets/024b82ac-b087-43d1-946a-c6683b146cec" />

## Table of Contents
- **1. B+ Tree Storage:** Ensures fast data retrieval for optimal database performance involving large datasets.
- **2. Write Ahead Logging (WAL) for Durability:** Ensures database integrity and durability through atomic and defensive operations. 
- **3. Page:** -> Use of pages as data structures to represent the nodes of the B+ tree in order to represent disk file structure instead of in-memory storage. 
## Features


## Incoming Features
- **3. Concurrent Reads/Writes with Locking:** Lock manager will handle database status, will likely involve some mutex through a lock manager to simplify this project. 
- **4. Caching with In-memory Tables:** When a new table is modified, read from, or accessed in some way, the data will be loaded directly into RAM for quick access. 
