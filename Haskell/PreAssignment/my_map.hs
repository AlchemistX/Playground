{-
  my_map.hs
-}
my_map:: (a -> b) -> [a] -> [b]
my_map f xs = foldr (\x base -> f x:base) [] xs 
