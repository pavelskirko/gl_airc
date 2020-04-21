# GL airC course

## Task 1. Basic signal generator

The main goal is to generate periodic signal with given amplitude, frequency, bit-depth, discretization and save it to the csv file.

### how to use:
  - run the program
  - create the track
  - add signal which fit to the track
  - save to the csv or output to console
  - have fun with csv analysis

## Task 2. Simple database

A client-server application capable to store a 3-column table of data in json-like structure, add, remove items and conduct a search, following commands transmitted in form of serialized json messages. 

A server stores database in a db.json file. When starting it initialize a table with 3 rows, which you can use as an example.

### how to use:
  - install json-c library on your system. In Ubuntu you can use the following:
  '''
  sudo apt install libjson-c-dev
  '''
  - use 'make' in both server and client directory
  - run db_server,  then db_client
  - use interface

