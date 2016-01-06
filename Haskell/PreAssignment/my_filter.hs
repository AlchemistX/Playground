{-
  my_filter.hs
  Multiline comment in Haskell by opening with {- and closing with -}.
-}
my_filter:: (a -> Bool) -> [a] -> [a]
my_filter f [] = []
my_filter f (x:xs) = if (f x)
                     then x:(my_filter f xs)
                     else my_filter f xs

