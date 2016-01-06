{-
  my_reverse.hs
-}
my_reverse xs = foldl (\x base -> base:x) [] xs 
