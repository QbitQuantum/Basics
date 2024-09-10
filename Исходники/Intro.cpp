void main(void)\n\
{  \n\
   float fTime0_X = parameters[0][0];\n\
   vec4 coreSeed = parameters[1];\n\
\n\
   vec3 rayDir = normalize(objectPosition * vec3(1.0, 0.6, 1.0));\n\
   vec3 camPos = vec3(0.0, 0.0, -parameters[0][1]);\n\
   \n\
   // rotate camera around y axis\n\
   float alpha = parameters[0][2] * 4.5f;\n\
   camPos.xz = vec2(cos(alpha)*camPos.x - sin(alpha)*camPos.z,\n\
                    sin(alpha)*camPos.x + cos(alpha)*camPos.z);\n\
   rayDir.xz = vec2(cos(alpha)*rayDir.x - sin(alpha)*rayDir.z,\n\
                    sin(alpha)*rayDir.x + cos(alpha)*rayDir.z);\n\
   \n\
   vec3 rayPos = camPos;\n\
   float sceneSize = 8.0;\n\
   vec3 totalColor = vec3(0.);\n\
   float stepSize;\n\
   float totalDensity = 0.0;\n\
   float stepDepth = 0.0; // how far I went already.\n\
   \n\
   for(int step = 0; length(rayPos)<sceneSize && totalDensity < 0.9 && step < 50; step++)\n\
   {      \n\
      float implicitVal;\n\
      \n\
      // This stuff is the transformation information from previous stuff\n\
	  float transer = parameters[0][3];\n\
      vec4 prevQuaternion = vec4(cos(transer), sin(transer), sin(transer * 1.3), sin(transer * 2.7));\n\
      prevQuaternion = normalize(prevQuaternion);\n\
      float prevLength = 1.0;\n\
      vec3 prevMover = vec3(0.0);\n\
      vec3 prevColor = vec3(1.0, 0.4, 0.2);\n\
      \n\
      // Multiple boxes\n\
      implicitVal = 1.0e10;\n\
      \n\
      for (int loop = 0; loop < 12; loop++)\n\
      {\n\
         vec4 newQuaternion;\n\
         float newLength;\n\
         vec3 newMover;\n\
         vec3 newColor;\n\
         \n\
         mat3 prevRotationMatrix = quaternionToMatrix(prevQuaternion);\n\
\n\
         // Loop for solid stuff\n\
         vec4 seed = coreSeed;\n\
         for (int k = 0; k < 4; k++)\n\
         {\n\
            seed = randomIteration(seed);\n\
            vec4 quaternion = normalize(seed - vec4(0.5));\n\
            mat3 rotationMatrix = quaternionToMatrix(quatMult(quaternion, prevQuaternion));\n\
            vec3 lengthes = seed.xyz * seed.xyz * seed.xyz * seed.xyz * vec3(0.2) + vec3(0.05);\n\
            lengthes *= prevLength;\n\
            vec3 mover = 0.5*seed.wzx - vec3(0.25);\n\
            mover = (mover * prevRotationMatrix * prevLength) + prevMover;\n\
            float curImplicitVal = getDistance(rotationMatrix, lengthes, mover, rayPos);\n\
            implicitVal = min(implicitVal, curImplicitVal);\n\
         }\n\
         \n\
         // Non-solid:\n\
         float nonSolidDist = 1.0e10;\n\
         for (int k = 0; k < 2; k++)\n\
         {\n\
            seed = randomIteration(seed);\n\
            vec4 quaternion = normalize(seed - vec4(0.5));\n\
            quaternion = quatMult(quaternion, prevQuaternion);\n\
            vec3 lengthes = seed.xyz * vec3(0.3) + vec3(0.25);\n\
            lengthes *= prevLength;\n\
            vec3 mover = 0.5*seed.wzx - vec3(0.25);\n\
            mover = (mover * prevRotationMatrix * prevLength) + prevMover;\n\
            float curImplicitVal = getSphereDistance(lengthes.x, mover, rayPos);\n\
            if (curImplicitVal < nonSolidDist)\n\
            {\n\
               nonSolidDist = curImplicitVal;\n\
               newQuaternion = quaternion;\n\
               newLength = lengthes.x;\n\
               newMover = mover;\n\
               newColor = seed.xyz;\n\
            }\n\
         }\n\
         \n\
         if (nonSolidDist > implicitVal)\n\
         {\n\
            // I will not get closer than where I am now.\n\
            break;\n\
         }\n\
         else\n\
         {\n\
            prevQuaternion = newQuaternion;\n\
            prevLength = newLength;\n\
            prevMover = newMover;\n\
            prevColor = 0.5 * prevColor + 0.5 * newColor;      \n\
         }\n\
      }\n\
      \n\
      // I need to do this distance related to for the DOF!      \n\
      totalColor += vec3(1./50., 1./70., 1./90.) *\n\
                    1.7 / exp(abs(implicitVal*5.) + 0.0) * 1.8;\n\
      totalDensity += 1./ 15. / exp(abs(implicitVal*10.0) + 0.5);\n\
                      // *(1.0 - cos(fTime0_X*3.)*0.5);\n\
      //if (implicitVal < 0.0)\n\
      stepDepth += abs(implicitVal) * 0.95;      \n\
      {\n\
         // TODO: I could make this distance-related, with offset to get the size right?\n\
         float localDensity = implicitVal < 0.0 ? 1.0 : 0.0;\n\
         totalColor = totalColor + (1.-totalDensity) * prevColor * localDensity;\n\
         totalDensity = totalDensity + (1.05-totalDensity) * localDensity;\n\
      }\n\
      \n\
      stepSize = abs(implicitVal) * 0.99;\n\
      stepSize = max(0.005 * stepDepth, stepSize);\n\
      rayPos += rayDir * stepSize;\n\
   }\n\
   \n\
   float grad = normalize(rayDir).y;\n\
   totalColor += (1.-totalDensity) * (grad * vec3(0.0,-0.4,-0.3) + (1.-grad)*vec3(0.0,0.4,0.6));\n\
   \n\
   gl_FragColor = vec4(totalColor-vec3(0.0), 1.0);\n\
}\n\