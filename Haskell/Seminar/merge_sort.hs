merge:: Ord a => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge xall@(x:xs) yall@(y:ys) = if x < y then x : merge xs yall  else y : merge xall ys

mergeSort:: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [a] = [a]
mergeSort xs = 
  merge firstHalf secondHalf
  where
    firstHalf = mergeSort $ take half xs
    secondHalf = mergeSort $ drop half xs
    half = length xs `div` 2
