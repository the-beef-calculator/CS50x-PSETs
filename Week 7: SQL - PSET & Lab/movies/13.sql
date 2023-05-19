SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
JOIN movies m2 ON s2.movie_id = m2.id
JOIN stars s3 ON m2.id = s3.movie_id
JOIN people p3 ON s3.person_id = p3.id
JOIN stars s4 ON m.id = s4.movie_id
JOIN people p4 ON s4.person_id = p4.id
WHERE p2.name = 'Kevin Bacon'
  AND p2.birth = 1958
  AND p3.id <> p.id
  AND p4.name <> 'Kevin Bacon';
