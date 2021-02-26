(define (cycle? l)
  (define check (list 1))
  (define (loop ll)
    (cond ((null? ll) #f)
          ((eq? check (car ll)) #t)
          (else (begin (set-car! ll check) (loop (cdr ll))))))
  (loop l))