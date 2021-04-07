/* 
010102030405060708090a0b0c0d0e0f00
01020008080000000002006D00100000

0002000404000000000900C900420000

000203040501010000000b0c0d0e0f00
0102030405060708090a0b0c0d0e0f00

------------------------ rawDataToProtocol end ------------------------
------------------------ rawDataToProtocol start ------------------------

//json结构如下所示：

jsonMap {
  method: 'thing.attribute.post',
  params: {
    workstatus: undefined,
    mode: 346,
    shockAbsorbtionOnOff: 2,
    targetSpeed: 0.3,
    speed: 0.4,
    sportingSteps: 1286,
    distance: 4608090,
    sportingTime: 42,
    burnCalories: 308.5,
    heartRate: 14,
    errorCode: undefined,
    workSwitch: undefined
  },
  version: '1.0.0'
}

/////////////////////////////////////////////////////////////////
{
  "identifier":"workstatus",
  "name":"工作状态",
  "accessMode":"r",
  "required":false,
  "dataType":{
      "type":"enum",
      "specs":{
          "0":"停止",
          "1":"运行中",
          "2":"暂停"
      }
  }
},

{
  "identifier":"workSwitch",
  "name":"启动开关",
  "accessMode":"rw",
  "required":false,
  "dataType":{
      "type":"enum",
      "specs":{
          "0":"关闭",
          "1":"打开",
          "2":"暂停"
      }
  }
}




/////////////////////////////////////////////////  11-9更新最小物模型

{
    "schema":"https://iotx-tsl.oss-ap-southeast-1.aliyuncs.com/schema.json",
    "profile":{
        "productKey":"3419"
    },
    "properties":[
        {
            "identifier":"onlinestate",
            "name":"在线状态",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"bool",
                "specs":{
                    "0":"离线",
                    "1":"在线"
                }
            }
        },


        {
            "identifier":"workstatus",
            "name":"工作状态",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"enum",
                "specs":{
                    "0":"停止",
                    "1":"运行中",
                    "2":"暂停"
                }
            }
        },

        {
            "identifier":"workSwitch",
            "name":"启动开关",
            "accessMode":"rw",
            "required":false,
            "dataType":{
                "type":"enum",
                "specs":{
                    "0":"关闭",
                    "1":"打开",
                    "2":"暂停"
                }
            }
        }

        {
            "identifier":"speed",
            "name":"速度",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"double",
                "specs":{
                    "min":"0.0",
                    "max":"14.0",
                    "unit":"km/h",
                    "unitName":"千米每小时",
                    "step":"0.1",
                    "defaultValue":"0.0"
                }
            }
        },

        {
            "identifier":"targetSpeed",
            "name":"目标速度",
            "accessMode":"rw",
            "required":true,
            "dataType":{
                "type":"double",
                "specs":{
                    "min":"0",
                    "max":"14",
                    "unit":"km/h",
                    "unitName":"千米每小时",
                    "step":"1",
                    "defaultValue":"0"
                }
            }
        },

        {
            "identifier":"burnCalories",
            "name":"消耗热量",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"double",
                "specs":{
                    "min":"0.0",
                    "max":"9999.9",
                    "unit":"kcal",
                    "unitName":"千卡路里",
                    "step":"0.1",
                    "defaultValue":"0.0"
                }
            }
        },

        {
            "identifier":"errorCode",
            "name":"错误码",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"enum",
                "specs":{
                    //值定义留给厂商
                }
            }
        },
        {
            "identifier":"sportingTime",
            "name":"运动时间",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"int",
                "specs":{
                    "min":"0",
                    "max":"2147483647",
                    "unit":"′",
                    "unitName":"秒",
                    "step":"1",
                    "defaultValue":"0"
                }
            }
        },
        {
            "identifier":"distance",
            "name":"运动距离",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"int",
                "specs":{
                    "min":"0",
                    "max":"65536",
                    "unit":"m",
                    "unitName":"米",
                    "step":"1",
                    "defaultValue":"0"
                }
            }
        },
        {
            "identifier":"heartRate",
            "name":"心率",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"int",
                "specs":{
                    "min":"0",
                    "max":"255",
                    "step":"1",
                    "defaultValue":"0"
                }
            }
        },
        
        {
            "identifier":"sportingSteps",
            "name":"运动步数",
            "accessMode":"r",
            "required":false,
            "dataType":{
                "type":"int",
                "specs":{
                    "min":"0",
                    "max":"9999999",
                    "unit":"stepCount",
                    "unitName":"步",
                    "step":"1",
                    "defaultValue":"0"
                }
            }
        },
        
        
    ]
}

















*/


