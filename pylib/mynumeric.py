def sum(lo: int, hi: int) -> int:
    i = lo  # type: int
    out = 0  # type: int

    while True:
        out += i
        i += 1
        if i == hi:
            break

    return out
