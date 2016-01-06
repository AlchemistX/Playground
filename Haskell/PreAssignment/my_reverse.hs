{-
  my_reverse.hs
-}
my_reverse:: [a] -> [a]
my_reverse xs = foldl (\x base -> base:x) [] xs 
