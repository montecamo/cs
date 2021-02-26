(define (make-account init-balance)
  (let ((balance init-balance)
        (history '()))
    (define (withdraw amount)
      (set! balance (- balance amount))
      (set! history (append history (list (list 'withdraw amount))))
      balance)
    (define (deposit amount)
      (set! balance (+ balance amount)) 
      (set! history (append history (list (list 'deposit amount))))
      balance)
    (define (dispatch msg)
      (cond
        ((eq? msg 'withdraw) withdraw)
        ((eq? msg 'deposit) deposit) 
        ((eq? msg 'balance) balance) 
        ((eq? msg 'transactions) history) 
        ((eq? msg 'init-balance) init-balance)))
    dispatch))