/**
 * Restarting simulations
 * 
 * This example demonstrates how to restart a simulation
 * using a binary file. A shearing sheet ring simulation is used, but
 * the same method can be applied to any other type of simulation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "rebound.h"

void heartbeat(struct reb_simulation* const r);

int main(int argc, char* argv[]){
    {
        printf("Running simulation until t=1.\n");
        struct reb_simulation* r = reb_create_simulation();
        r->integrator    = REB_INTEGRATOR_SEI;
        r->collision    = REB_COLLISION_DIRECT;
        r->collision_resolve = reb_collision_resolve_hardsphere;
        r->boundary     = REB_BOUNDARY_SHEAR;
        r->Omega      = 1.;    
        r->dt         = 1e-4*2.*M_PI; 
        r->exact_finish_time = 1; // Finish exactly at tmax in reb_integrate(). Default is already 1.
        r->nghostx = 1; r->nghosty = 1; r->nghostz = 0;
        reb_configure_box(r,2.,1,1,1);

        while (r->N<50){
            struct reb_particle p = {0};
            p.x  = ((double)rand()/(double)RAND_MAX-0.5)*r->boxsize.x;
            p.y  = ((double)rand()/(double)RAND_MAX-0.5)*r->boxsize.y;
            p.z  = 0.1*((double)rand()/(double)RAND_MAX-0.5)*r->boxsize.z;
            p.vy = -1.5*p.x*r->Omega;
            p.m  = 0.0001;
            p.r  = 0.1;
            reb_add(r, p);
        }
        r->heartbeat = heartbeat;
        reb_integrate(r,1.);
        printf("Saving simulation to binary file and freeing up memory.\n");
        reb_output_binary(r, "restart.bin");
        reb_free_simulation(r);
        r = NULL;
    }
    {
        printf("Creating simulation from binary file and integrating until t=2.\n");
        struct reb_simulation* r = reb_create_simulation_from_binary("restart.bin");
        // Need to reset function pointers
        r->heartbeat = heartbeat;
        reb_integrate(r,2.);
        printf("Done.\n");
    }
}

void heartbeat(struct reb_simulation* const r){
    // Dummy.
}
