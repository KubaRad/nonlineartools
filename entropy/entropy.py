from nonlineartools._fastentropy import _sampen

import numpy as np


def sampen(x, m, r, recalculate_std=True):
    r1 = r*np.std(x) if recalculate_std else r
    return _sampen(x, m, r1)

