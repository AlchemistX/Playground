import Data.List

-- 15
my_maximum [] = 0
--my_maximum (x:xs) = max x (my_maximum xs)
my_maximum xs = foldl1 max xs

my_minimum [] = 0
--my_minimum (x:xs) = min x (my_minimum xs)
my_minimum xs = foldl1 min xs

-- 16
my_span:: (a -> Bool) -> [a] -> ([a], [a])
my_span p [] = ([], [])
my_span p xs = (takeWhile p xs, dropWhile p xs)

-- 17
my_compose:: (b -> c) -> (a -> b) -> a -> c
f `my_compose` g = \ a -> f (g a)

-- 18
rmDuplicate:: (Ord a) => [a] -> [a]
--rmDuplicate xs = map head ((group.sort) xs)
rmDuplicate = map head.group.sort
