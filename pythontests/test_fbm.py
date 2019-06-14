import unittest
import numpy as np
import fbmpy

class TestFBM(unittest.TestCase):

    def test_1d_bridge(self):
        N = 128
        X = np.random.normal(0, 1, N-1)
        B = fbmpy.fractional_brownian_bridge_1d(0.2, N, X)


        self.assertEqual(0, B[0])
        self.assertEqual(0, B[-1])

    def test_2d_bridge(self):
        N = 128
        X = np.random.normal(0, 1, (N-1)**2)
        B = fbmpy.fractional_brownian_bridge_2d(0.2, N, X).reshape(N+1, N+1)


        for i in range(N+1):
            self.assertEqual(0, B[i,0])
            self.assertEqual(0, B[0,i])
            self.assertEqual(0, B[i,-1])
            self.assertEqual(0, B[-1,i])

    def test_3d_bridge(self):
        N = 32
        X = np.random.normal(0, 1, (N-1)**2)
        B = fbmpy.fractional_brownian_bridge_3d(0.2, N, X).reshape(N+1, N+1, N+1)


        for i in range(N+1):
            for j in range(N+1):
                self.assertEqual(0, B[i,j, 0])
                self.assertEqual(0, B[0,j, i])
                self.assertEqual(0, B[i,j,-1])
                self.assertEqual(0, B[-1,i,j])
                self.assertEqual(0, B[i,-1,j])
                self.assertEqual(0, B[i,0,j])

if __name__ == '__main__':
    unittest.main()
