my_scanl _ base [] = [base]
my_scanl f base (x:xs) = base : my_scanl f (f base x) xs

my_it_scanl f x = scanl (\a _ -> f a) x (repeat 1)

my_fib_scanl = 1:scanl (+) 1 my_fib_scanl
