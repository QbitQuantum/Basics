        TEST_F(JSDeviceTest, getEndpoints) {
            EndpointID endpointId1{20};
            EndpointID endpointId2{21};
            ZEndpoint endpoint1{NwkAddr {1}, endpointId1, 30, 31, 32, {ClusterID {50}}, {ClusterID {51}}};
            ZEndpoint endpoint2{NwkAddr {1}, endpointId2, 30, 31, 32, {ClusterID {60}}, {ClusterID {61}}};
            ZDevice zDevice{extAddress, NwkAddr(1), 0, {endpoint1, endpoint2}};
            V8_SETUP

            Local<Object> objectEndpoint1 = Object::New(isolate);
            Local<Object> objectEndpoint2 = Object::New(isolate);

            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));

            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(*jsEndpoint, createInstance(isolate, extAddress, endpointId1)).WillOnce(
                    Return(objectEndpoint1));
            EXPECT_CALL(*jsEndpoint, createInstance(isolate, extAddress, endpointId2)).WillOnce(
                    Return(objectEndpoint2));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.getEndpoints();");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsArray(), true);
            Local<Array> array = result.As<Array>();

            ASSERT_THAT(array->Length(), 2);
            ASSERT_THAT(array->Get(0)->IsObject(), true);
            ASSERT_THAT(array->Get(1)->IsObject(), true);
            Local<Object> jszEndpoint0 = array->Get(0).As<Object>();
            Local<Object> jszEndpoint1 = array->Get(1).As<Object>();
            ASSERT_THAT(jszEndpoint0->GetIdentityHash(), Eq(objectEndpoint1->GetIdentityHash()));
            ASSERT_THAT(jszEndpoint1->GetIdentityHash(), Eq(objectEndpoint2->GetIdentityHash()));
        }