{-
  my_zipWith.hs
-}
my_zipWith:: (a -> b -> c) -> [a] -> [b] -> [c]
my_zipWith f [] _ = []
my_zipWith f _ [] = []
my_zipWith f (x:xs) (y:yx) = f x y : my_zipWith f xs yx

--my_unzip xs = foldr (\x base -> (fst x:fst base , snd x: snd base)) ([],[]) xs
my_unzip xs = foldr (\(a, b) (as, bs) -> (a:as, b:bs)) ([],[]) xs
