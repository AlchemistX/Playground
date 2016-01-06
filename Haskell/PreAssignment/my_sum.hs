{-
  my_sum.hs
-}
my_sum:: Num a => [a] -> a
my_sum xs = foldr (\x y -> x + y) 0 xs
