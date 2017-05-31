# NoSqlDb
As an academic project, we tried to capture the present trend in NoSQL Databases and build a custom version which is similar to Redis, Casandra etc to get more insight into how NoSQL Databases work internally.
1. Implemented the Database using template classes so that any Generic type of elements can be stored in the Database.
2. Implemented the persistence functionality. The Database can be persisted to an XML on a command. However, the project is open for extension to persist data in a different format like JSON etc.
3.The Database can be restored back from an external XML or any persistent disk.
4. Implemented Time-based persistence and Count-based persistence.The Database can be persisted after a time stamp or after the number of writes has reached a threshold value. The User can choose between time-saving or saving based on count ber of writes.
5.Implemented an extensive search mechanism based on which we can retrieve the value of a key, the children of a key, the category of a key, the time stamp of a key etc using complex Regex expressions.
6.Implemented compound queries and querying on the query results obtained.
