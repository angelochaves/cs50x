SELECT title
FROM (((people
INNER JOIN stars ON people.id=stars.person_id)
INNER JOIN movies ON stars.movie_id=movies.id)
INNER JOIN ratings ON ratings.movie_id=movies.id)
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;