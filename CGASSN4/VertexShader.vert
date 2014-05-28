uniform float rockscale;
uniform vec3 vnormal;

void main() {	
   vec3 v = gl_Vertex;
   t.x = gl_Vertex.x + (vnormal.x * rockscale);
   t.y = gl_Vertex.y + (vnormal.y * rockscale);
   t.z = gl_Vertex.z + (vnormal.z * rockscale);
   gl_Position = gl_ModelViewProgectionMatrix * v;
}