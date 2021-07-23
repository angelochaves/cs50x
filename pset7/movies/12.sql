SELECT title
FROM ((people
INNER JOIN stars ON people.id=stars.person_id)
INNER JOIN movies ON stars.movie_id=movies.id)
WHERE people.name = 'Johnny Depp'
INTERSECT
SELECT title
FROM ((people
INNER JOIN stars ON people.id=stars.person_id)
INNER JOIN movies ON stars.movie_id=movies.id)
WHERE people.name = 'Helena Bonham Carter';