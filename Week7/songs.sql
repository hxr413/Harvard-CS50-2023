-- In 1.sql, write a SQL query to list the names of all songs in the database.
SELECT name from songs;

-- In 2.sql, write a SQL query to list the names of all songs in increasing order of tempo.
SELECT name FROM songs ORDER BY tempo;

-- In 3.sql, write a SQL query to list the names of the top 5 longest songs, in descending order of length.
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- In 4.sql, write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75.
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- In 5.sql, write a SQL query that returns the average energy of all the songs.
SELECT AVG(energy) FROM songs;

 -- In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
 -- You should not make any assumptions about what Post Malone’s artist_id is.
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

-- In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.
-- You should not make any assumptions about what Drake’s artist_id is.
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');

-- In 8.sql, write a SQL query that lists the names of the songs that feature other artists.
-- Songs that feature other artists will include “feat.” in the name of the song.
SELECT name FROM songs WHERE name LIKE '%feat.%'