data BinTree a = Empty | Fork a (BinTree a) (BinTree a) deriving Show
instance Functor BinTree where
  fmap f Empty = Empty
  fmap f (Fork a l r) = Fork (f a) (fmap f l) (fmap f r)

myTree1 = Fork 'a' (Fork 'b' Empty Empty) (Fork 'c' Empty (Fork 'd' Empty Empty))
myTree2 = Fork 1 (Fork 2 Empty Empty) (Fork 3 Empty (Fork 4 Empty Empty))
myTree3 = Fork 1 (Fork 2 (Fork 5 Empty Empty) Empty) (Fork 3 Empty (Fork 4 Empty Empty))
sizeBinTree:: BinTree a -> Int
sizeBinTree Empty = 0
sizeBinTree (Fork a l r) = 1 + sizeBinTree l + sizeBinTree r

sumBinTree:: Num a => BinTree a -> a
sumBinTree Empty = 0
sumBinTree (Fork a l r) = a + sumBinTree l + sumBinTree r

