uniform vec2 u_resolution;

vec3 normalize(vec3 v){
    float h = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    v.x/=h;
    v.y/=h;
    v.z/=h;
    return v;
}

vec2 sphIntersect(in vec3 ro, in vec3 rd, float ra) {
        float b = dot(ro, rd);
        float c = dot(ro, ro) - ra * ra;
        float h = b * b - c;
        if(h < 0.0) return vec2(-1.0);
        h = sqrt(h);
        return vec2(-b - h, -b + h);
}

vec3 castRay(vec3 ro, vec3 rd) {
        vec2 it = sphIntersect(ro, rd, 1.0);
        if(it.x < 0.0) return vec3(0.0);
        vec3 itPos = ro + rd * it.x;
        vec3 n = itPos;
        vec3 light = normalize(vec3(-1.0, -2.0, -3.0));
        float diffuse = max(0.0, dot(light, n));
        vec3 col = vec3(diffuse);
        return col;
}

void main() {
        vec2 uv = (gl_TexCoord[0].xy -0.5) * u_resolution / u_resolution.y;
        gl_FragColor = vec4(uv, 0.0, 1.0);
        vec3 rayOrigin = vec3(-5.0, 0.0, 0.0);
        vec3 rayDirection = normalize(vec3(1.0, uv));
        vec3 col = castRay(rayOrigin, rayDirection);
        gl_FragColor = vec4(col, 1.0);
}

