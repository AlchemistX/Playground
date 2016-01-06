{-
  my_map.hs
-}
my_map f xs = foldr (\x base -> f x:base) [] xs 
