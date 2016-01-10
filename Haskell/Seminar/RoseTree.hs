data RoseTree a = Branch a [RoseTree a] deriving Show

instance Functor RoseTree where
  --fmap:: (a -> b) -> RoseTree a -> RoseTree b
  --fmap f (Branch a b) = Branch (f a) (map fmap f b)
  fmap f (Branch a b) = Branch (f a) (map (\t -> fmap f t) b)

myRTree1 = Branch 'a' [Branch 'b' []] 
