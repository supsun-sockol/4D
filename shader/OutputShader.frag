uniform vec2 u_resolution;
uniform vec3 u_mouse;
uniform vec4 u_pos;

const float MAX_DIST = 99999.0;

mat2 rot(float a) {
        float s = sin(a);
        float c = cos(a);
        return mat2(c, -s, s, c);
}

vec4 normalize(vec4 v){
    float h = sqrt(v.x*v.x+v.y*v.y+v.z*v.z+ v.w*v.w);
    v.x/=h;
    v.y/=h;
    v.z/=h;
    v.w/=h;
    return v;
}

vec2 sphIntersect(in vec4 ro, in vec4 rd, float ra) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - ra * ra;
    float h = b * b - c;
    if(h < 0.0) return vec2(-1.0);
    h = sqrt(h);
    return vec2(-b - h, -b + h);
}

/*vec2 boxIntersection(in vec4 ro, in vec4 rd, in vec4 rad, out vec4 oN)  {
    vec4 m = 1.0 / rd;
    vec4 n = m * ro;
    vec4 k = abs(m) * rad;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
    float tN = max(max(t1.x, t1.y), t1.z);
    float tF = min(min(t2.x, t2.y), t2.z);
    if(tN > tF || tF < 0.0) return vec2(-1.0);
    oN = -sign(rd) * step(t1.yzx, t1.xyz) * step(t1.zxy, t1.xyz);
    return vec2(tN, tF);
}*/

vec3 castRay(vec4 ro, vec4 rd) {
    vec2 minIt = vec2(MAX_DIST);
    vec2 it;
    vec4 n;
    vec4 spherePos = vec4(0.0, -1.0, 0.0, 0.0);
    it = sphIntersect(ro - spherePos, rd, 1.0);
    if(it.x > 0.0 && it.x < minIt.x) {
        minIt = it;
        vec4 itPos = ro + rd * it.x;
        n = itPos - spherePos;
    }
    /*
    vec3 boxN;
    vec3 boxPos = vec3(0.0, 2.0, 0.0);
    it = boxIntersection(ro - boxPos, rd, vec3(1.0), boxN);
    if(it.x > 0.0 && it.x < minIt.x) {
        minIt = it;
        n = boxN;
    }*/
    if(minIt.x == MAX_DIST) return vec3(0.0);
    vec4 light = normalize(vec4(-1.0, -2.0, -3.0, -4.0));
    //float diffuse = max(0.0, dot(light, n))+0.1;
    float diffuse = (dot(light, n)+1.0)/2.0;
    vec3 col = vec3(diffuse);
    return col;
}

void main() {
    vec2 uv = (gl_TexCoord[0].xy -0.5) * u_resolution / u_resolution.y;
    vec4 rayOrigin = u_pos;
    vec4 rayDirection = normalize(vec4(1.0, uv, 0.0));
    rayDirection.zx *= rot(-u_mouse.y);
    rayDirection.xy *= rot(-u_mouse.x);
    rayDirection.xw *= rot(-u_mouse.z);
    vec3 col = castRay(rayOrigin, rayDirection);
    gl_FragColor = vec4(col, 1.0);
}

