import fbmpy
import numpy as np
import matplotlib.pyplot as plt
dimensions = {
    1 : fbmpy.fractional_brownian_bridge_1d,
    2 : fbmpy.fractional_brownian_bridge_2d,
    3 : fbmpy.fractional_brownian_bridge_3d
}

cut = {
    1 : lambda x,n : x[:-1],
    2 : lambda x,n : x.reshape(n+1, n+1)[:-1, :-1],
    3 : lambda x, n : x.reshape(n+1, n+1, n+1)[:-1, :-1, :-1],
    }

Hs = [0.2, 0.5, 0.75]

for dim in dimensions.keys():
    for H in Hs:
        resolutions = 2**np.arange(4,9)
        errors = []
        X = np.random.normal(0, 1, resolutions[-1]**dim)
        for resolution in resolutions:

            fbm_coarse = cut[dim](dimensions[dim](H, int(resolution//2), X),
                                  resolution//2)
            fbm = cut[dim](dimensions[dim](H, int(resolution), X),
                           resolution)
            for d in range(dim):
                # upscale
                fbm_coarse = np.repeat(fbm_coarse, 2, d)
                
            error = np.sum(abs(fbm_coarse-fbm))/resolution**dim
            errors.append(error)

        p = plt.loglog(resolutions, errors, '-o', label=f'$H={H}$, $d={dim}$')
        poly = np.polyfit(np.log(resolutions), np.log(errors), 1)
        plt.loglog(resolutions, np.exp(poly[1])*resolutions**poly[0], '--',
                   color=p[0].get_color(),
                   label=f'$\\mathcal{{O}}(N^{{{poly[0]:.1f}}})$',
                   basex=2, basey=2)
        plt.xticks(resolutions,
                   [f'${x}^{dim}$' for x in resolutions])
    plt.legend()
    plt.xlabel(f"Resolution $N^{{{dim}}}$")
    plt.ylabel(f"Cauchy error $||B^N-B^{{2N}}||_{{L^1(D)}}$")
    plt.show()
            

            
