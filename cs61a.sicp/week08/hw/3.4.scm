(define (make-account balance password) 
  ((lambda (incorrect-attempts)
    (define (withdraw amount)
      (if (>= balance amount)
        (begin (set! balance (- balance amount)) balance)
        "Insufficient funds"))
    (define (deposit amount)
      (set! balance (+ balance amount))
      balance)
    (define (valid-password) (set! incorrect-attempts 0))
    (define (incorrect-password . args) 
      (if (>= incorrect-attempts 2) 
        (call-cops)
        (begin (set! incorrect-attempts (+ incorrect-attempts 1)) "Incorrect password")))
    (define (call-cops) "I'm calling cops, fucking thief")
    (define (dispatch pass m)
      (if (not (eq? pass password)) 
        incorrect-password
        (begin (valid-password) (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              (else (error "Unknown request: MAKE-ACCOUNT"
                           m))))))
    dispatch)
  0))
