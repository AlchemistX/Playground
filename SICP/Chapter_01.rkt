#lang planet neil/sicp
(#%require r5rs/init)

;; Exercise 1.1
10
(+ 5 3 4)
(- 9 1)
(/ 6 2)
(+ (* 2 4) (- 4 6))
(define a 3)
(define b (+ a 1))
(+ a b (* a b))
(= a b)
(if (and (> b a) (< b (* a b)))
    b
    a)
(cond ((= a 4) 6)
      ((= b 4) (+ 6 7 a))
      (else 25))
(+ 2 (if (> b a) b a))
(* (cond ((> a b) a)
         ((< a b) b)
         (else -1))
   (+ a 1))

;; Exercise 1.2
;; Translate the following expression into prefix form
(/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5))))) (* 3 (- 6 2) (- 2 7)))

;; Exercise 1.3
;; Define a procedure that takes three numbers as arguments and returns the sum of the squares of the two larger numbers.
(define (min a b c)
  (if (< a b)
      (if (< a c) a c)
      (if (< b c) b c)))
(define (square a)
  (* a a))
(define (sum-of-squares a b c)
  (- (+ (square a) (square b) (square c)) (square (min a b c))))

(sum-of-squares 3 2 1)
(sum-of-squares 1 3 2)
(sum-of-squares 3 1 2)

