/*
 * sphere_on_sphere.c
 *
 * Code generation for function 'sphere_on_sphere'
 *
 * C source code generated on: Sat Oct 18 11:59:48 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "Body.h"
#include "Body_sphere.h"
#include "Simulator.h"

/* Type Definitions */
#ifndef struct_stb3atYu6PXQt604qRfuYIG
#define struct_stb3atYu6PXQt604qRfuYIG

typedef struct stb3atYu6PXQt604qRfuYIG
{
  char_T name[4];
  char_T type[7];
  real_T bodyID;
  real_T bodyContactID;
  real_T bodyDynamicID;
  boolean_T dynamic;
  boolean_T active;
  real_T mass;
  real_T u[3];
  real_T quat[4];
  real_T J[9];
  real_T nu[6];
  real_T Fext[6];
  real_T Aext[6];
  real_T mu;
  real_T numJoints;
  boolean_T visible;
  real_T color[3];
  real_T facealpha;
  real_T edgealpha;
  real_T AABB_min[3];
  real_T AABB_max[3];
  boolean_T collides;
  real_T radius;
  real_T num_sphere_verts;
  real_T height;
  real_T plane_normal[9];
  real_T num_verts;
  real_T num_edges;
  real_T num_faces;
} c_struct_T;

#else

typedef struct stb3atYu6PXQt604qRfuYIG c_struct_T;

#endif

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
struct_T sphere_on_sphere(void)
{
  struct_T sim;
  struct_T_size expl_temp_elems_sizes;
  d_struct_T expl_temp_data;
  char_T s1_name[4];
  int32_T i0;
  int32_T i;
  char_T s1_type_data[7];
  real_T s1_quat[4];
  real_T s1_J[9];
  real_T s1_nu[6];
  real_T s1_Fext[6];
  real_T s1_Aext[6];
  real_T s1_AABB_min[3];
  real_T s1_AABB_max[3];
  real_T s1_plane_normal[3];
  int8_T s1_u[3];
  static const int8_T iv0[3] = { 0, 0, -1 };

  struct_T_size b_expl_temp_elems_sizes;
  char_T s2_name[4];
  char_T s2_type_data[7];
  real_T s2_quat[4];
  real_T s2_J[9];
  real_T s2_nu[6];
  real_T s2_Fext[6];
  real_T s2_Aext[6];
  real_T s2_color[3];
  real_T s2_AABB_min[3];
  real_T s2_AABB_max[3];
  real_T s2_plane_normal[3];
  real_T s2_u[3];
  static const real_T dv0[3] = { -0.05, 0.05, 1.25 };

  b_struct_T expl_temp;
  char_T t2_name[4];
  char_T t2_type[7];
  real_T t2_u[3];
  real_T t2_quat[4];
  real_T t2_J[9];
  real_T t2_nu[6];
  real_T t2_Fext[6];
  real_T t2_Aext[6];
  real_T t2_color[3];
  real_T t2_AABB_min[3];
  real_T t2_AABB_max[3];
  real_T t2_plane_normal[3];
  c_struct_T P_data;
  static const char_T cv0[5] = { 'p', 'l', 'a', 'n', 'e' };

  static const int8_T point[3] = { 0, 0, -3 };

  static const int8_T y[3] = { 0, 0, 1 };

  c_struct_T tmp_data;
  c_struct_T b_tmp_data;
  c_struct_T body_data[3];

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  RPI-MATLAB-Simulator */
  /*  http://code.google.com/p/rpi-matlab-simulator/ */
  /*  */
  /*  Initialize simulator */
  Simulator(0.01, &sim);

  /* sim.drawContacts = true; */
  sim.MAX_STEP = 500.0;
  sim.draw = FALSE;

  /* sim.H_dynamics = @LCPdynamics;  */
  /* sim.H_solver = @Lemke; */
  /* sim.H_dynamics = @mLCPdynamics;  */
  /*  A sphere */
  Body_sphere(&expl_temp_data, &expl_temp_elems_sizes);
  for (i0 = 0; i0 < 4; i0++) {
    s1_name[i0] = expl_temp_data.name[i0];
  }

  i = expl_temp_elems_sizes.type[0] * expl_temp_elems_sizes.type[1] - 1;
  for (i0 = 0; i0 <= i; i0++) {
    s1_type_data[i0] = expl_temp_data.type[i0];
  }

  for (i = 0; i < 4; i++) {
    s1_quat[i] = expl_temp_data.quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    s1_J[i0] = expl_temp_data.J[i0];
  }

  for (i = 0; i < 6; i++) {
    s1_nu[i] = expl_temp_data.nu[i];
    s1_Fext[i] = expl_temp_data.Fext[i];
    s1_Aext[i] = expl_temp_data.Aext[i];
  }

  for (i0 = 0; i0 < 3; i0++) {
    s1_AABB_min[i0] = expl_temp_data.AABB_min[i0];
    s1_AABB_max[i0] = expl_temp_data.AABB_max[i0];
    s1_plane_normal[i0] = expl_temp_data.plane_normal[i0];
    s1_u[i0] = iv0[i0];
  }

  b_Body_sphere(&expl_temp_data, &b_expl_temp_elems_sizes);
  for (i0 = 0; i0 < 4; i0++) {
    s2_name[i0] = expl_temp_data.name[i0];
  }

  i = b_expl_temp_elems_sizes.type[0] * b_expl_temp_elems_sizes.type[1] - 1;
  for (i0 = 0; i0 <= i; i0++) {
    s2_type_data[i0] = expl_temp_data.type[i0];
  }

  for (i = 0; i < 4; i++) {
    s2_quat[i] = expl_temp_data.quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    s2_J[i0] = expl_temp_data.J[i0];
  }

  for (i = 0; i < 6; i++) {
    s2_nu[i] = expl_temp_data.nu[i];
    s2_Fext[i] = expl_temp_data.Fext[i];
    s2_Aext[i] = expl_temp_data.Aext[i];
  }

  for (i0 = 0; i0 < 3; i0++) {
    s2_color[i0] = expl_temp_data.color[i0];
    s2_AABB_min[i0] = expl_temp_data.AABB_min[i0];
    s2_AABB_max[i0] = expl_temp_data.AABB_max[i0];
    s2_plane_normal[i0] = expl_temp_data.plane_normal[i0];
    s2_u[i0] = dv0[i0];
  }

  Body(&expl_temp);
  for (i0 = 0; i0 < 4; i0++) {
    t2_name[i0] = expl_temp.name[i0];
  }

  for (i0 = 0; i0 < 7; i0++) {
    t2_type[i0] = expl_temp.type[i0];
  }

  for (i = 0; i < 3; i++) {
    t2_u[i] = expl_temp.u[i];
  }

  for (i = 0; i < 4; i++) {
    t2_quat[i] = expl_temp.quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    t2_J[i0] = expl_temp.J[i0];
  }

  for (i = 0; i < 6; i++) {
    t2_nu[i] = expl_temp.nu[i];
    t2_Fext[i] = expl_temp.Fext[i];
    t2_Aext[i] = expl_temp.Aext[i];
  }

  for (i0 = 0; i0 < 3; i0++) {
    t2_color[i0] = expl_temp.color[i0];
    t2_AABB_min[i0] = expl_temp.AABB_min[i0];
    t2_AABB_max[i0] = expl_temp.AABB_max[i0];
    t2_plane_normal[i0] = expl_temp.plane_normal[i0];
  }

  for (i0 = 0; i0 < 4; i0++) {
    P_data.name[i0] = t2_name[i0];
  }

  for (i0 = 0; i0 < 7; i0++) {
    P_data.type[i0] = t2_type[i0];
  }

  P_data.bodyID = 0.0;
  P_data.bodyContactID = 0.0;
  P_data.bodyDynamicID = 0.0;
  P_data.dynamic = TRUE;
  P_data.active = FALSE;
  P_data.mass = 1.0;
  for (i = 0; i < 3; i++) {
    P_data.u[i] = t2_u[i];
  }

  for (i = 0; i < 4; i++) {
    P_data.quat[i] = t2_quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    P_data.J[i0] = t2_J[i0];
  }

  for (i = 0; i < 6; i++) {
    P_data.nu[i] = t2_nu[i];
    P_data.Fext[i] = t2_Fext[i];
    P_data.Aext[i] = t2_Aext[i];
  }

  P_data.mu = 0.5;
  P_data.numJoints = 0.0;
  P_data.visible = TRUE;
  for (i0 = 0; i0 < 3; i0++) {
    P_data.color[i0] = t2_color[i0];
  }

  P_data.facealpha = 0.7;
  P_data.edgealpha = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    P_data.AABB_min[i0] = t2_AABB_min[i0];
    P_data.AABB_max[i0] = t2_AABB_max[i0];
  }

  P_data.collides = TRUE;
  P_data.radius = 1.0;
  P_data.num_sphere_verts = 7.0;
  P_data.height = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    P_data.plane_normal[i0] = t2_plane_normal[i0];
  }

  P_data.num_verts = 0.0;
  P_data.num_edges = 0.0;
  P_data.num_faces = 0.0;
  for (i0 = 0; i0 < 5; i0++) {
    P_data.type[i0] = cv0[i0];
  }

  for (i0 = 0; i0 < 3; i0++) {
    P_data.color[i0] = 0.6;
  }

  P_data.dynamic = FALSE;

  /*  We require that all plane bodies are static */
  for (i = 0; i < 3; i++) {
    P_data.u[i] = (real_T)point[i];
    P_data.plane_normal[i] = (real_T)y[i];
  }

  for (i0 = 0; i0 < 4; i0++) {
    tmp_data.name[i0] = s1_name[i0];
  }

  i = expl_temp_elems_sizes.type[1] - 1;
  for (i0 = 0; i0 <= i; i0++) {
    tmp_data.type[i0] = s1_type_data[i0];
  }

  tmp_data.bodyID = 0.0;
  tmp_data.bodyContactID = 0.0;
  tmp_data.bodyDynamicID = 0.0;
  tmp_data.dynamic = TRUE;
  tmp_data.active = FALSE;
  tmp_data.mass = 20.0;
  for (i = 0; i < 3; i++) {
    tmp_data.u[i] = (real_T)s1_u[i];
  }

  for (i = 0; i < 4; i++) {
    tmp_data.quat[i] = s1_quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    tmp_data.J[i0] = s1_J[i0];
  }

  for (i = 0; i < 6; i++) {
    tmp_data.nu[i] = s1_nu[i];
    tmp_data.Fext[i] = s1_Fext[i];
    tmp_data.Aext[i] = s1_Aext[i];
  }

  tmp_data.mu = 0.5;
  tmp_data.numJoints = 0.0;
  tmp_data.visible = TRUE;
  for (i0 = 0; i0 < 3; i0++) {
    tmp_data.color[i0] = 0.7;
  }

  tmp_data.facealpha = 0.7;
  tmp_data.edgealpha = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    tmp_data.AABB_min[i0] = s1_AABB_min[i0];
    tmp_data.AABB_max[i0] = s1_AABB_max[i0];
  }

  tmp_data.collides = TRUE;
  tmp_data.radius = 2.0;
  tmp_data.num_sphere_verts = 25.0;
  tmp_data.height = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    tmp_data.plane_normal[i0] = s1_plane_normal[i0];
  }

  tmp_data.num_verts = 0.0;
  tmp_data.num_edges = 0.0;
  tmp_data.num_faces = 0.0;
  for (i0 = 0; i0 < 4; i0++) {
    b_tmp_data.name[i0] = s2_name[i0];
  }

  i = b_expl_temp_elems_sizes.type[1] - 1;
  for (i0 = 0; i0 <= i; i0++) {
    b_tmp_data.type[i0] = s2_type_data[i0];
  }

  b_tmp_data.bodyID = 0.0;
  b_tmp_data.bodyContactID = 0.0;
  b_tmp_data.bodyDynamicID = 0.0;
  b_tmp_data.dynamic = TRUE;
  b_tmp_data.active = FALSE;
  b_tmp_data.mass = 1.0;
  for (i = 0; i < 3; i++) {
    b_tmp_data.u[i] = s2_u[i];
  }

  for (i = 0; i < 4; i++) {
    b_tmp_data.quat[i] = s2_quat[i];
  }

  for (i0 = 0; i0 < 9; i0++) {
    b_tmp_data.J[i0] = s2_J[i0];
  }

  for (i = 0; i < 6; i++) {
    b_tmp_data.nu[i] = s2_nu[i];
    b_tmp_data.Fext[i] = s2_Fext[i];
    b_tmp_data.Aext[i] = s2_Aext[i];
  }

  b_tmp_data.mu = 0.5;
  b_tmp_data.numJoints = 0.0;
  b_tmp_data.visible = TRUE;
  for (i0 = 0; i0 < 3; i0++) {
    b_tmp_data.color[i0] = s2_color[i0];
  }

  b_tmp_data.facealpha = 0.7;
  b_tmp_data.edgealpha = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    b_tmp_data.AABB_min[i0] = s2_AABB_min[i0];
    b_tmp_data.AABB_max[i0] = s2_AABB_max[i0];
  }

  b_tmp_data.collides = TRUE;
  b_tmp_data.radius = 0.25;
  b_tmp_data.num_sphere_verts = 15.0;
  b_tmp_data.height = 1.0;
  for (i0 = 0; i0 < 3; i0++) {
    b_tmp_data.plane_normal[i0] = s2_plane_normal[i0];
  }

  b_tmp_data.num_verts = 0.0;
  b_tmp_data.num_edges = 0.0;
  b_tmp_data.num_faces = 0.0;
  body_data[0] = P_data;
  body_data[1] = tmp_data;
  body_data[2] = b_tmp_data;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  RPI-MATLAB-Simulator */
  /*  http://code.google.com/p/rpi-matlab-simulator/ */
  /*  */
  /*  Adds the column vector of body structs to the sim struct.   */
  /*  INPUTS: */
  /*        sim  - A simulation struct created with Simulator(). */
  /*        body - A body struct or vector of body  */
  /*                structs created with Body().   */
  /*  Allow body to contain multiple bodies, but require a vector. */
  /*  Force a row vector. */
  /*  Update body information */
  for (i = 0; i < 3; i++) {
    /*  Force position vectors to be column vectors */
    P_data = body_data[i];

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  Kinematic update with or without velocity */
    /*  Update the position and orientation of a body, including world coordinates and face normals. */
    /*  INPUTS:  */
    /*        B       - A Body_mesh struct to be updated.  */
    /*        h       - The timestep size in seconds.   */
    /*        newNu   - (optional) The body's velocity at the end of the current timestep. */
    /*  Do not update static bodies */
    /* if ~B.dynamic, return; end */
    /*  If there is a newNu assigned */
    /*  Velocity  */
    for (i0 = 0; i0 < 6; i0++) {
      P_data.nu[i0] = body_data[i].nu[i0] + body_data[i].Fext[i0] / body_data[i]
        .mass * 0.0;
    }

    /*  Translation */
    for (i0 = 0; i0 < 3; i0++) {
      P_data.u[i0] += 0.0 * P_data.nu[i0];
    }

    /*  Rotation  */
    body_data[i] = P_data;
    body_data[i].bodyID = 1.0 + (real_T)i;
  }

  /*  Update and return the sim struct.  */
  /* sim.bodies = [ sim.bodies body ]; */
  sim.num_bodies = 3.0;
  for (i = 0; i < 3; i++) {
    if (body_data[i].dynamic) {
      sim.num_dynamicBodies++;

      /* sim.bodies(i).bodyDynamicID = sim.num_dynamicBodies; */
    } else {
      /* sim.bodies(i).bodyDynamicID = -1; */
    }
  }

  /*  Add bodies to simulator */
  /*  Run the simulator! */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  RPI-MATLAB-Simulator */
  /*  http://code.google.com/p/rpi-matlab-simulator/ */
  /*  */
  /*  Runs a simulator  */
  /*  Initialize graphics  */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  RPI-MATLAB-Simulator */
  /*  http://code.google.com/p/rpi-matlab-simulator/ */
  /*  */
  /*  This function initializes all of the graphics associated with a */
  /*  simulation.  */
  /* figure();  hold on;  */
  /*     %% Init body graphics */
  /*      for b=1:length(sim.bodies) */
  /*         sim.bodies(b) = body_draw_init(sim.bodies(b));   */
  /*      end */
  /*       */
  /*      %% Init bounding box graphics */
  /*      if sim.drawBoundingBoxes  */
  /*          Vbb = zeros(8,3);  */
  /*          for b=1:sim.num_bodies */
  /*              M = sim.bodies(b).AABB_max; */
  /*              m = sim.bodies(b).AABB_min;  */
  /*              Vbb(1,:) = [m(1) m(2) m(3)];  % Verts of BBox */
  /*              Vbb(2,:) = [m(1) M(2) m(3)]; */
  /*              Vbb(3,:) = [M(1) M(2) m(3)]; */
  /*              Vbb(4,:) = [M(1) m(2) m(3)]; */
  /*              Vbb(5,:) = [m(1) m(2) M(3)]; */
  /*              Vbb(6,:) = [m(1) M(2) M(3)]; */
  /*              Vbb(7,:) = [M(1) M(2) M(3)]; */
  /*              Vbb(8,:) = [M(1) m(2) M(3)]; */
  /*              Ebb = [ Vbb(1,:); Vbb(2,:) */
  /*                      Vbb(3,:); Vbb(4,:) */
  /*                      Vbb(1,:); Vbb(5,:) */
  /*                      Vbb(6,:); Vbb(7,:) */
  /*                      Vbb(8,:); Vbb(5,:) */
  /*                      Vbb(6,:); Vbb(2,:) */
  /*                      Vbb(3,:); Vbb(7,:) */
  /*                      Vbb(8,:); Vbb(4,:) ]; */
  /*              sim.bodies(b).bboxHandle = plot3(Ebb(:,1),Ebb(:,2),Ebb(:,3),'b'); */
  /*          end */
  /*      end */
  /*       */
  /*      %% Init joint graphics */
  /*      if sim.drawJoints */
  /*          for j=1:length(sim.joints) */
  /*             Jnt = sim.joints(j);  */
  /*             p1 = Jnt.P1;  */
  /*             x1 = Jnt.X1; */
  /*             y1 = Jnt.Y1; */
  /*             z1 = Jnt.Z1;  */
  /*             p2 = Jnt.P2; */
  /*             x2 = Jnt.X2; */
  /*             y2 = Jnt.Y2; */
  /*             z2 = Jnt.Z2;  */
  /*              */
  /*            Jnt.drawn = true;  */
  /*            Jnt.P1Handle = plot3(p1(1),p1(2),p1(3),'r*'); */
  /*            Jnt.P1_X_AxisHandle = plot3([p1(1) x1(1)],[p1(2) x1(2)],[p1(3) x1(3)],'r'); */
  /*            Jnt.P1_Y_AxisHandle = plot3([p1(1) y1(1)],[p1(2) y1(2)],[p1(3) y1(3)],'g'); */
  /*            Jnt.P1_Z_AxisHandle = plot3([p1(1) z1(1)],[p1(2) z1(2)],[p1(3) z1(3)],'b'); */
  /*            %Jnt.P1_Z_pointHandle = plot3(z1(1),z1(2),z1(3),'bo'); */
  /*   */
  /*            Jnt.P2Handle = plot3(p2(1),p2(2),p2(3),'r*'); */
  /*            Jnt.P2_X_AxisHandle = plot3([p2(1) x2(1)],[p2(2) x2(2)],[p2(3) x2(3)],'r'); */
  /*            Jnt.P2_Y_AxisHandle = plot3([p2(1) y2(1)],[p2(2) y2(2)],[p2(3) y2(3)],'g'); */
  /*            Jnt.P2_Z_AxisHandle = plot3([p2(1) z2(1)],[p2(2) z2(2)],[p2(3) z2(3)],'b'); */
  /*            %Jnt.P2_Z_pointHandle = plot3(z2(1),z2(2),z2(3),'bo'); */
  /*   */
  /*            Jnt.labelHandle = text(p1(1),p1(2),p1(3)+0.5,['Joint ' num2str(Jnt.jointID)]); */
  /*   */
  /*            sim.joints(j) = Jnt;  */
  /*          end */
  /*      end */
  /*       */
  /*      %% Set default plot properties */
  /*      view(3);  */
  /*      grid on;  */
  /*      axis equal;  */
  /*      xlabel('X'); ylabel('Y'); zlabel('Z');  */
  /*       */
  /*      if ~exist('OCTAVE_VERSION','var'), rotate3d; end */
  /* disp('Simulating without GUI, make sure you have set sim.MAX_STEP to a reasonable value.'); end */
  /*  Turn "on" gravity */
  /* if sim.gravity, sim = sim_setGravity( sim ); end */
  /*  Remove to run without pause */
  /* pause();  */
  /*     %% Simulation loop  */
  /* tic; */
  /* sim.START_TIME = tic;  */
  for (i = 0; i < 500; i++) {
    /* tic;                                % Start step timer */
    sim.time += 0.01;
    sim.step++;

    /*  Run user-defined function: here it is wam_controller.m */
    /*  Generate a contact set, and identify participating dynamic bodies  */
    /*          if ~isempty( sim.H_collision_detection ) */
    /*              sim = feval( sim.H_collision_detection, sim );  */
    /*          end */
    /*  Formulate dynamics and solve for new body velocities */
    /* sim.newNU = []; */
    /* fprintf('The number of contacts is: %6d\n', numContact); */
    /*  Apply results from solution, as well as update bodies not in contact.    */
    /*  This function iterates over all simulation bodies and updates their  */
    /*  position as well as type-specific properties like vertex positions for  */
    /*  mesh bodies.   */
    /*  Apply results from solution, as well as update bodies not in contact.    */
    /*  Correct joint errors */
    /*  Update title and graphics */
    /*          if sim.draw */
    /*              figure(sim.figure); */
    /*              title(['Timestep: ' num2str(sim.step)]); */
    /*              if sim.drawContacts, sim = sim_drawContacts(sim); end */
    /*              if sim.drawJoints,   sim = sim_drawJoints(sim);   end */
    /*              axis equal; */
    /*              drawnow;  */
    /*          else */
    /*              %disp(['Step ' num2str(sim.step) ' took ' num2str(toc) ' seconds']); */
    /*          end */
    /*  Record data for playback  */
    /* if sim.record, sim = sim_record(sim); end  */
  }

  /*  End simulation loop */
  /*  sim.TOTAL_TIME = toc(sim.START_TIME);  */
  /*  disp(['Simulation finished!  Total time: ' num2str(sim.TOTAL_TIME) ' seconds.']); */
  /*  End sim_run() */
  return sim;
}

/* End of code generation (sphere_on_sphere.c) */
