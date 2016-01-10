{-
  my_fold.hs
-}
my_foldr:: (a -> b -> b) -> b -> [a] -> b
my_foldr f base [] = base
my_foldr f base (x:xs) = f x (my_foldr f base xs)

my_foldl:: (b -> a -> b) -> b -> [a] -> b
my_foldl f base [] = base
my_foldl f base (x:xs) = my_foldl f (f base x) xs

