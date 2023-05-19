SELECT DISTINCT p.name
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN stars s2 ON s1.movie_id = s2.movie_id
JOIN people p ON s2.person_id = p.id
JOIN people kb ON s1.person_id = kb.id
WHERE p.name <> 'Kevin Bacon'
AND kb.name = 'Kevin Bacon'
AND kb.birth = 1958;
