{-
 my_iterate.hs
 -}
my_iterate f x = x : my_iterate f (f x)
