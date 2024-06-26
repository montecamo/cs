(define (in-order? pred l)
  (define (helper prev l)
    (if (null? l) 
      #t
      (let ((curr (car l)))
        (if (pred prev curr)
          (helper curr (cdr l))
          #f))))
  (helper (first l) (butfirst l)))

(define (order-checker pred)
  (lambda (l)
    (define (helper prev l)
      (if (null? l) 
        #t
        (let ((curr (car l)))
          (if (pred prev curr)
            (helper curr (cdr l))
            #f))))
    (helper (first l) (butfirst l))))
