import Data.List

fib = 1:1:zipWith (+) fib (tail fib)
ex_20 = sum(takeWhile (<4000000) [d | d <- fib, even d])
ex_21 = maximum [x*y | x <- [100..999], y <- [100..999], isPalindrome (x*y)]
        where isPalindrome n = show n == reverse (show n)
ex_22 = [(x,y,z) | x <- [1..998], y <- [x+1..998], let z = 1000 - x - y, isPyta x y z]
        where isPyta x y z = (x^2 + y^2 == z^2)
