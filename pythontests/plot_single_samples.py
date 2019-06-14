import fbmpy
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

motion_type=None
if len(sys.argv) == 1 or sys.argv[1] == 'bridge':
    dimensions = {
        1 : fbmpy.fractional_brownian_bridge_1d,
        2 : fbmpy.fractional_brownian_bridge_2d,
        3 : fbmpy.fractional_brownian_bridge_3d
    }
    motion_type='bridge'
elif sys.argv[1] == 'motion':
    dimensions = {
        1 : fbmpy.fractional_brownian_motion_1d,
        2 : fbmpy.fractional_brownian_motion_2d,
        3 : fbmpy.fractional_brownian_motion_3d
    }
    motion_type='motion'
else:
    print(f"Unknown type {sys.argv[1]}. Possible choices:")
    print("\t* motion\n\t*bridge")
    exit(1)

cut = {
    1 : lambda x,n : x[:-1],
    2 : lambda x,n : x.reshape(n+1, n+1)[:-1, :-1],
    3 : lambda x, n : x.reshape(n+1, n+1, n+1)[:-1, :-1, :-1],
    }

Hs = [0.2, 0.5, 0.75]
dimensions_keys = sorted([k for k in dimensions.keys()])
for dim in dimensions.keys():
    if dim == 1:
        num_slices = 1
    else:
        num_slices = 4

    f, axes = plt.subplots(num_slices, len(Hs), sharey='all',
                           figsize=(len(Hs)*8,  6*num_slices),
                           sharex='all')
    f.suptitle(f"Fractional Brownian {motion_type}, slices of {dim}D")

    if dim < 3:
        num2dplots = 1
    else:
        num2dplots = 4
    if dim > 1:
        f2d, axes2d = plt.subplots(num2dplots, len(Hs), sharey='all',
                           figsize=(len(Hs)*8,  6*num2dplots),
                               sharex='all', subplot_kw={'projection': '3d'})
    
        f2d.suptitle(f"Fractional Brownian {motion_type}, 2D slices of {dim}D")

    resolution = 128
    X = np.random.normal(0, 1, (resolution-1)**dim)
    for n, H in enumerate(Hs):
        fbm = cut[dim](dimensions[dim](H, int(resolution), X), resolution)
        spatial_x = np.linspace(0, 1, resolution)
        if dim == 1:
            
            axes[n].plot(spatial_x, fbm)
            axes[n].set_title(f'$H={H}$')
            axes[n].set_xlabel("$x$")
            axes[n].set_ylabel("$B^H(\\omega; x)$")
        if dim == 2:
            for k in range(0,2):
                axes[k, n].plot(spatial_x, fbm[:,((k+1)*resolution)//3])
                axes[k, n].set_title(f'$H={H}$, $y={(k+1)/3:.1f}$')
                axes[k, n].set_xlabel("$x$")
                axes[k, n].set_ylabel("$B^H(\\omega; x, y)$")

                axes[k+2, n].plot(spatial_x, fbm[((k+1)*resolution)//3,:])
                axes[k+2, n].set_title(f'$H={H}$, $x={(k+1)/3:.1f}$')
                axes[k+2, n].set_xlabel("$y$")
                axes[k+2, n].set_ylabel("$B^H(\\omega; x, y)$")

        elif dim == 3:
            for k in range(0,2):
                axes[k, n].plot(spatial_x, fbm[resolution//2,:,((k+1)*resolution)//3])
                axes[k, n].set_title(f'$H={H}$, $y={(k+1)/3:.1f}, x=1/2$')
                axes[k, n].set_xlabel("$y$")
                axes[k, n].set_ylabel("$B^H(\\omega; x, y, z)$")

                axes[k+2, n].plot(spatial_x, fbm[((k+1)*resolution)//3,:,resolution//2])
                axes[k+2, n].set_title(f'$H={H}$, $x={(k+1)/3:.1f}, z=1/2$')
                axes[k+2, n].set_xlabel("$y$")
                axes[k+2, n].set_ylabel("$B^H(\\omega; x, y, z)$")

        x, y = np.mgrid[0:1:resolution*1j, 0:1:resolution*1j]
        if dim == 2:
            axes2d[n].plot_surface(x, y, fbm)
            axes2d[n].set_title(f"$H={H}$")
            axes2d[n].set_xlabel("$x$")
            axes2d[n].set_ylabel("$y$")
        if dim == 3:
            for k in range(0,2):
                axes2d[k, n].plot_surface(x,y,fbm[:,:,((k+1)*resolution)//3])
                axes2d[k, n].set_title(f'$H={H}$, $y={(k+1)/3:.1f}$')
                axes2d[k, n].set_xlabel("$x$")
                axes2d[k, n].set_ylabel("$z$")
                axes2d[k, n].set_zlabel("$B^H(\\omega; x, y, z)$")

                axes2d[k+2, n].plot_surface(x, y, fbm[((k+1)*resolution)//3,:,:])
                axes2d[k+2, n].set_title(f'$H={H}$, $x={(k+1)/3:.1f}$')
                axes2d[k+2, n].set_xlabel("$y$")
                axes2d[k+2, n].set_ylabel("$z$")
                axes2d[k+2, n].set_zlabel("$B^H(\\omega; x, y, z)$")


            

    
    plt.tight_layout()

    f.savefig(f'slice_{motion_type}_{dim}d.png')
    if dim > 1:
        f2d.savefig(f'slice_2d_{motion_type}_{dim}d.png')
    plt.show()
    

            
