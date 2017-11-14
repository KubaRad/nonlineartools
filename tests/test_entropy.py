import os
import pkg_resources
import numpy as np
import logging
from unittest import TestCase
from entropy.entropy import *
from math import inf, isinf, isnan

_TEST_FILE_NAME = "test.dat"
_SAMPENTEST_FILE_NAME = "sampentest.dat"

_FILE_PATH = "data"

_TEST_EXPECTED = [(100, 0, 2.219284),
    (100, 1, 1.884072),
    (100, 2, 2.448539),

    (1000, 0, 3.258906),
    (1000, 1, 1.837773),
    (1000, 2, 1.845717),

    (10000, 0, 3.490305),
    (10000, 1, 2.345856),
    (10000, 2, 2.257106),

    (100000, 0, 2.392242),
    (100000, 1, 2.585857),
    (100000, 2, 2.373165),
    (100000, 3, 2.210238),
    (100000, 4, 2.095717),
    (100000, 5, 1.978219),
    (100000, 6, 1.878340),
    (100000, 7, 1.681759),
    (100000, 8, 3.178054),
    (100000, 9, inf)]


def _provide_test_data_filename():
    resource_package = __name__
    resource_path = os.path.join(_FILE_PATH, _TEST_FILE_NAME)
    return pkg_resources.resource_filename(resource_package, resource_path)


def _provide_sampentest_data_filename():
    resource_package = __name__
    resource_path = os.path.join(_FILE_PATH, _SAMPENTEST_FILE_NAME)
    return pkg_resources.resource_filename(resource_package, resource_path)


class TestEntropy(TestCase):
    def test_sample_entropy(self):
        buf = np.genfromtxt(_provide_test_data_filename(), delimiter=',', skip_header=0)
        for case in _TEST_EXPECTED:
            data_len = case[0]
            m = case[1]
            expected_result = case[2]
            logging.getLogger('show.this').info('data len: {} m: {} expected: {}'.format(data_len,m,expected_result))
            result = sampen(buf[0:data_len], m, 0.2, recalculate_std=False)
            logging.getLogger('show.this').info('acquired result: {}'.format(result))
            if isnan(result):
                continue
            if isinf(expected_result):
                self.assertTrue(isinf(result))
            else:
                self.assertAlmostEqual(expected_result, result, places=6)

