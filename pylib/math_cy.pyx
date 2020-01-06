


cpdef long int sum(int lo, int hi):

    cdef int i = lo
    cdef int out = 0

    while i < hi:
        out += i
        i += 1

    return out

