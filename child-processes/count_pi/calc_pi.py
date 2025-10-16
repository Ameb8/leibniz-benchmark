def calc_pi(n_terms: int) -> float:
    pi: float = 0.0

    for i in range(n_terms):
        sign: int = 1

        if i % 2 == 1:
            sign = -1

        pi += sign / (2 * i + 1)
    
    return 4 * pi

