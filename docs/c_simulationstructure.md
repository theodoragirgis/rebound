# Simulation structure

This page describes the `reb_simulation` structure. 
It contains the configuration and the current state of one REBOUND simulation.
The following code will allocated a new REBOUND simulation and initialize the all variables:
```c
struct reb_simulation* r = reb_create_simulation();
```
If you want to release the memory allocated in the above function call, use the corresponding `_free` function:
```c
reb_free_simulation(r);
```
This will free all data associated with the simulation such as particles and the simulation structure itself.

The following table lists the important members of `struct reb_simulation`.
To keep this documentation concise, the members which are only intended for internal use are not documented here. 

Member                      | Description
--------------------------- | --------------
`double t`                  | Current simulation time. 
`double G`                  | Gravitational constant. Default: 1. 
`double softening`          | Gravitational softening parameter. Default: 0. 
`double dt`                 | Current timestep. 
`double dt_last_done`       | Last timestep used.
`unsigned long long steps_done` | Number of timesteps completed.
`int N`                     | Current number of particles on this node. 
`int N_var`                 | Total number of variational particles. Default: 0.
`int var_config_N`          | Number of variational configuration structs. Default: 0.
`struct reb_variational_configuration* var_config` |  ///< These configuration structs contain details on variational particles. 


```
int     N_active;               ///< Number of massive particles included in force calculation (default: N). Particles with index >= N_active are considered testparticles.
int     testparticle_type;      ///< Type of the particles with an index>=N_active. 0 means particle does not influence any other particle (default), 1 means particles with index < N_active feel testparticles (similar to MERCURY's small particles). Testparticles never feel each other.
int     testparticle_hidewarnings;      ///< Hide testparticle warnings if 1. Default: 0.
struct reb_hash_pointer_pair* particle_lookup_table; ///< Array of pairs that map particles' hashes to their index in the particles array.
int     hash_ctr;               ///< Counter for number of assigned hashes to assign unique values.
int     N_lookup;               ///< Number of entries in the particle lookup table.
int     allocatedN_lookup;      ///< Number of lookup table entries allocated.
int     allocatedN;             ///< Current maximum space allocated in the particles array on this node. 
struct reb_particle* particles; ///< Main particle array. This contains all particles on this node.  
struct reb_vec3d* gravity_cs;   ///< Vector containing the information for compensated gravity summation 
int     gravity_cs_allocatedN;  ///< Current number of allocated space for cs array
struct reb_treecell** tree_root;///< Pointer to the roots of the trees. 
int     tree_needs_update;      ///< Flag to force a tree update (after boundary check)
double opening_angle2;          ///< Square of the cell opening angle \f$ \theta \f$. 
enum REB_STATUS status;         ///< Set to 1 to exit the simulation at the end of the next timestep. 
int     exact_finish_time;      ///< Set to 1 to finish the integration exactly at tmax. Set to 0 to finish at the next dt. Default is 1. 

unsigned int force_is_velocity_dependent;   ///< Set to 1 if integrator needs to consider velocity dependent forces.  
unsigned int gravity_ignore_terms; ///< Ignore the gravity form the central object (1 for WHFast, 2 for WHFastHelio, 0 otherwise)
double output_timing_last;      ///< Time when reb_output_timing() was called the last time. 
unsigned long display_clock;    ///< Display clock, internal variable for timing refreshs.
int save_messages;              ///< Set to 1 to ignore messages (used in python interface).
char** messages;                ///< Array of strings containing last messages (only used if save_messages==1). 
double exit_max_distance;       ///< Exit simulation if distance from origin larger than this value 
double exit_min_distance;       ///< Exit simulation if distance from another particle smaller than this value 
double usleep;                  ///< Wait this number of microseconds after each timestep, useful for slowing down visualization.  
struct reb_display_data* display_data; /// < Datastructure stores visualization related data. Does not have to be modified by the user. 
int track_energy_offset;        ///< Track energy change during collisions and ejections (default: 0).
double energy_offset;           ///< Energy offset due to collisions and ejections (only calculated if track_energy_offset=1).
double walltime;                ///< Walltime in seconds used by REBOUND for this simulation (integration only, not visualization, heartbeat function, etc).
uint32_t python_unit_l;         ///< Information only used for when working with units in python.
uint32_t python_unit_m;         ///< Information only used for when working with units in python.
uint32_t python_unit_t;         ///< Information only used for when working with units in python.
/** @} */

/**
 * \name Variables related to ghost/root boxes 
 * @{
 */
struct  reb_vec3d boxsize;  ///< Size of the entire box, root_x*boxsize. 
double  boxsize_max;        ///< Maximum size of the entire box in any direction. Set in box_init().
double  root_size;      ///< Size of a root box. 
int     root_n;         ///< Total number of root boxes in all directions, root_nx*root_ny*root_nz. Default: 1. Set in box_init().
int     root_nx;        ///< Number of root boxes in x direction. Default: 1. 
int     root_ny;        ///< Number of root boxes in y direction. Default: 1. 
int     root_nz;        ///< Number of root boxes in z direction. Default: 1. 
int     nghostx;        ///< Number of ghostboxes in x direction. 
int     nghosty;        ///< Number of ghostboxes in y direction. 
int     nghostz;        ///< Number of ghostboxes in z direction. 
/** @} */
#ifdef MPI
/**
 * \name Variables related to MPI 
 * @{
 */
int    mpi_id;                              ///< Unique id of this node (starting at 0). Used for MPI only.
int    mpi_num;                             ///< Number of MPI nodes. Used for MPI only.
MPI_Datatype mpi_particle;                  ///< MPI datatype corresponding to the C struct reb_particle. 
struct reb_particle** particles_send;       ///< Send buffer for particles. There is one buffer per node. 
int*   particles_send_N;                    ///< Current length of particle send buffer. 
int*   particles_send_Nmax;                 ///< Maximal length of particle send beffer before realloc() is needed. 
struct reb_particle** particles_recv;       ///< Receive buffer for particles. There is one buffer per node. 
int*   particles_recv_N;                    ///< Current length of particle receive buffer. 
int*   particles_recv_Nmax;                 ///< Maximal length of particle receive beffer before realloc() is needed. */

MPI_Datatype mpi_cell;                      ///< MPI datatype corresponding to the C struct reb_treecell. 
struct reb_treecell** tree_essential_send;  ///< Send buffer for cells. There is one buffer per node. 
int*   tree_essential_send_N;               ///< Current length of cell send buffer. 
int*   tree_essential_send_Nmax;            ///< Maximal length of cell send beffer before realloc() is needed. 
struct reb_treecell** tree_essential_recv;  ///< Receive buffer for cells. There is one buffer per node. 
int*   tree_essential_recv_N;               ///< Current length of cell receive buffer. 
int*   tree_essential_recv_Nmax;            ///< Maximal length of cell receive beffer before realloc() is needed. 
/** @} */
#endif // MPI

/**
 * \name Variables related to collision search and detection 
 * @{
 */
int collision_resolve_keep_sorted;      ///< Keep particles sorted if collision_resolve removes particles during a collision. 
struct reb_collision* collisions;       ///< Array of all collisions. 
int collisions_allocatedN;          ///< Size allocated for collisions.
double minimum_collision_velocity;      ///< Used for hard sphere collision model. 
double collisions_plog;             ///< Keep track of momentum exchange (used to calculate collisional viscosity in ring systems.
double max_radius[2];               ///< Two largest particle radii, set automatically, needed for collision search.
long collisions_Nlog;               ///< Keep track of number of collisions. 
/** @} */

/**
 * \name Variables related to the chaos indicator MEGNO 
 * @{
 */
int calculate_megno;    ///< Internal flag that determines if megno is calculated (default=0, but megno_init() sets it to the index of variational particles used for megno)
double megno_Ys;    ///< Running megno sum (internal use)
double megno_Yss;   ///< Running megno sum (internal use)
double megno_cov_Yt;    ///< covariance of MEGNO Y and t
double megno_var_t;     ///< variance of t 
double megno_mean_t;    ///< mean of t
double megno_mean_Y;    ///< mean of MEGNO Y
long   megno_n;     ///< number of covariance updates
unsigned int rand_seed; ///< seed for random number generator
/** @} */


/**
 * \name Variables related to SimulationArchive 
 * @{
 */
int    simulationarchive_version;           ///< Version of the SA binary format (1=original/, 2=incremental)
long   simulationarchive_size_first;        ///< (Deprecated SAV1) Size of the initial binary file in a SA
long   simulationarchive_size_snapshot;     ///< (Deprecated SAV1) Size of a snapshot in a SA (other than 1st), in bytes
double simulationarchive_auto_interval;     ///< Current sampling cadence, in code units
double simulationarchive_auto_walltime;     ///< Current sampling cadence, in wall time
unsigned long long simulationarchive_auto_step;  ///< Current sampling cadence, in time steps
double simulationarchive_next;              ///< Next output time (simulation tim or wall time, depending on wether auto_interval or auto_walltime is set)
unsigned long long simulationarchive_next_step; ///< Next output step (only used if auto_steps is set)
char*  simulationarchive_filename;          ///< Name of output file
/** @} */

/**
 * \name Variables describing the current module selection 
 * @{
 */
/**
 * @brief Available visualization options
 */
enum {
    REB_VISUALIZATION_NONE = 0,     ///< No visualization (default if OPENGL compiler flag is turned off)
    REB_VISUALIZATION_OPENGL = 1,   ///< OpenGL visualization (default if OPENGL compiler flag is turned on)
    REB_VISUALIZATION_WEBGL = 2,    ///< WebGL visualization, only usable from Jupyter notebook widget
    } visualization;
/**
 * @brief Available collision routines
 */
enum {
    REB_COLLISION_NONE = 0,     ///< Do not search for collisions (default)
    REB_COLLISION_DIRECT = 1,   ///< Direct collision search O(N^2)
    REB_COLLISION_TREE = 2,     ///< Tree based collision search O(N log(N))
    REB_COLLISION_MERCURIUS = 3,///< OBSOLETE, use REB_COLLISION_DIRECT instead
    REB_COLLISION_LINE = 4,     ///< Direct collision search O(N^2), looks for collisions by assuming a linear path over the last timestep
    REB_COLLISION_LINETREE = 5, ///< Tree-based collision search O(N log(N)), looks for collisions by assuming a linear path over the last timestep
    } collision;
/**
 * @brief Available integrators
 */
enum {
    REB_INTEGRATOR_IAS15 = 0,    ///< IAS15 integrator, 15th order, non-symplectic (default)
    REB_INTEGRATOR_WHFAST = 1,   ///< WHFast integrator, symplectic, 2nd order, up to 11th order correctors
    REB_INTEGRATOR_SEI = 2,      ///< SEI integrator for shearing sheet simulations, symplectic, needs OMEGA variable
    REB_INTEGRATOR_LEAPFROG = 4, ///< LEAPFROG integrator, simple, 2nd order, symplectic
    // REB_INTEGRATOR_HERMES = 5,   ///< HERMES Integrator, not available anymore. Use MERCURIUS instead.
    REB_INTEGRATOR_NONE = 7,     ///< Do not integrate anything
    REB_INTEGRATOR_JANUS = 8,    ///< Bit-wise reversible JANUS integrator.
    REB_INTEGRATOR_MERCURIUS = 9,///< MERCURIUS integrator 
    REB_INTEGRATOR_SABA = 10,    ///< SABA integrator family (Laskar and Robutel 2001)
    REB_INTEGRATOR_EOS = 11,     ///< Embedded Operator Splitting (EOS) integrator family (Rein 2019)
    } integrator;

/**
 * @brief Available boundary conditions
 */
enum {
    REB_BOUNDARY_NONE = 0,      ///< Do not check for anything (default)
    REB_BOUNDARY_OPEN = 1,      ///< Open boundary conditions. Removes particles if they leave the box 
    REB_BOUNDARY_PERIODIC = 2,  ///< Periodic boundary conditions
    REB_BOUNDARY_SHEAR = 3,     ///< Shear periodic boundary conditions, needs OMEGA variable
    } boundary;

/**
 * @brief Available gravity routines
 */
enum {
    REB_GRAVITY_NONE = 0,       ///< Do not calculate graviational forces
    REB_GRAVITY_BASIC = 1,      ///< Basic O(N^2) direct summation algorithm, choose this for shearing sheet and periodic boundary conditions
    REB_GRAVITY_COMPENSATED = 2,    ///< Direct summation algorithm O(N^2) but with compensated summation, slightly slower than BASIC but more accurate
    REB_GRAVITY_TREE = 3,       ///< Use the tree to calculate gravity, O(N log(N)), set opening_angle2 to adjust accuracy.
    REB_GRAVITY_MERCURIUS = 4,  ///< Special gravity routine only for MERCURIUS
    REB_GRAVITY_JACOBI = 5,     ///< Special gravity routine which includes the Jacobi terms for WH integrators 
    } gravity;
/** @} */


/**
 * \name Integrator structs (the contain integrator specific variables and temporary data structures) 
 * @{
 */
struct reb_simulation_integrator_sei ri_sei;        ///< The SEI struct 
struct reb_simulation_integrator_whfast ri_whfast;  ///< The WHFast struct 
struct reb_simulation_integrator_saba ri_saba;      ///< The SABA struct 
struct reb_simulation_integrator_ias15 ri_ias15;    ///< The IAS15 struct
struct reb_simulation_integrator_mercurius ri_mercurius;      ///< The MERCURIUS struct
struct reb_simulation_integrator_janus ri_janus;    ///< The JANUS struct 
struct reb_simulation_integrator_eos ri_eos;        ///< The EOS struct 
/** @} */

/**
 * \name Callback functions
 * @{
 */
/**
 * @brief This function allows the user to add additional (non-gravitational) forces.
 */
void (*additional_forces) (struct reb_simulation* const r);
/**
 * @brief This function allows the user to make changes before each timestep.
 */
void (*pre_timestep_modifications) (struct reb_simulation* const r);
/**
 * @brief This function allows the user to make changes after each timestep.
 */
void (*post_timestep_modifications) (struct reb_simulation* const r);
/**
 * @brief This function is called at the beginning of the simulation and at the end of
 * each timestep.
 */
void (*heartbeat) (struct reb_simulation* r);
/**
 * @brief This function is called at the beginning of the simulation and at the end of
 * each timestep.
 */
void (*display_heartbeat) (struct reb_simulation* r);
/**
 * @brief Return the coefficient of restitution. By default, it is NULL, assuming a coefficient of 1.
 * @details The velocity of the collision is given to allow for velocity dependent coefficients
 * of restitution.
 */
double (*coefficient_of_restitution) (const struct reb_simulation* const r, double v); 
/**
 * @brief Resolve collision within this function. By default, it is NULL, assuming hard sphere model.
 * @details A return value of 0 indicates that both particles remain in the simulation. A return value of 1 (2) indicates that particle 1 (2) should be removed from the simulation. A return value of 3 indicates that both particles should be removed from the simulation. 
 */
int (*collision_resolve) (struct reb_simulation* const r, struct reb_collision);

/**
 * @brief Free particle's ap pointer.  Called in reb_remove function.
 */
void (*free_particle_ap) (struct reb_particle* p);
/**
 * @brief Called in reb_free_pointers function for any necessary cleanup in external libraries that depend on the simulation structure.
 */
void (*extras_cleanup) (struct reb_simulation* r);
/** @} */

/**
 * \name Hooks for external libraries
 * @{
 */
/**
 * @brief Pointer to connect additional (optional) libraries, e.g., reboundx
 */
void* extras;
/** @} */
};

