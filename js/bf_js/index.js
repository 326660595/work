
/* 此脚本代码为demo演示使用，实际脚本代码请根据私有协议编辑运行 */

var  UP_RAW_VERSION  =  0x00;
var  UP_RAW_CMD  =  0x00;
var  DOWN_RAW_VERSION  =  0x00;
var  DOWN_RAW_CMD  =  0x80;
var  RAW_HEAD  =  [0x55,0xaa,0x00];

var THING_ATTRIBUTE_GET_CMD = 0x00,THING_ATTRIBUTE_GET = "thing.attribute.get";
var THING_ATTRIBUTE_SET_CMD = 0x01,THING_ATTRIBUTE_SET = "thing.attribute.set";
var THING_ATTRIBUTE_POST_CMD = 0x02,THING_ATTRIBUTE_POST = "thing.attribute.post";
var THING_ATTRIBUTE_ADJUST_CMD = 0x03,THING_ATTRIBUTE_ADJUST = "thing.attribute.adjust";
var THING_EVENT_POST_CMD = 0x04,THING_EVENT_POST = "thing.event.post";
var THING_SERVICE_INVOKE_CMD = 0x05,THING_SERVICE_INVOKE = "thing.service.invoke";
var THING_SERVICE_RESPONSE_CMD = 0x06,THING_SERVICE_RESPONSE = "thing.service.response";

var VERSION = '1.0.0';
var structStartId = 30;
//上报属性类型
var POST_TYPE = {//决定数据为几位
	PROTOCOL_PROP_TYPE_BOOL: 0,
	PROTOCOL_PROP_TYPE_INT8: 1,
	PROTOCOL_PROP_TYPE_UINT8: 2,
	PROTOCOL_PROP_TYPE_INT16: 3,
	PROTOCOL_PROP_TYPE_UINT16: 4,
	PROTOCOL_PROP_TYPE_INT32: 5,
	PROTOCOL_PROP_TYPE_UINT32: 6,
	PROTOCOL_PROP_TYPE_INT64: 7,
	PROTOCOL_PROP_TYPE_UINT64: 8,
	PROTOCOL_PROP_TYPE_FLOAT32: 9, 
	PROTOCOL_PROP_TYPE_FLOAT64: 10,
	PROTOCOL_PROP_TYPE_STRING: 11,
	PROTOCOL_PROP_TYPE_DATE: 12,
	PROTOCOL_PROP_TYPE_STRUCT:13
};

var SET_TYPE = {//决定数据为几位
  PROTOCOL_PROP_TYPE_BOOL: 1,
  PROTOCOL_PROP_TYPE_VALUE: 2,
  PROTOCOL_PROP_TYPE_DOUBLE:3,
  PROTOCOL_PROP_TYPE_ENUM: 4,
  PROTOCOL_PROP_TYPE_FAULT: 5
}

//通信协议中的所有属性
var g_attrTypeMap = {
  workstatus:{
    /*工作状态*/
    action:0,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
    swap:{//前面是协议中的参数  后面对应的是平台上的参数
      0:0,//关闭
      1:3,//待机
      1:37,//运行
      2:2,//暂停
    },
  },

  mode:{
    /*模式*/
    action:1,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
    swap:{//前面是协议中的参数  后面对应的是平台上的参数
      1:346,//减脂模式
      2:345,//自由模式
      3:347,//健康小跑模式
    },
  },
  
  shockAbsorbtionOnOff:{
    /*减震功能*/
    action:2,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
    swap:{//前面是协议中的参数  后面对应的是平台上的参数
      1:1,//沙滩
      2:2,//草地
      3:3,//塑胶跑道
      4:4,//公路
    },
  },

  targetSpeed:{
    /*目标速度*/
    action:3,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
  },
  
  speed:{
    /*速度*/
    action:4,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
  },
    
  sportingSteps:{
    /*运动步数*/
    action:5,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT16,SET_TYPE.PROTOCOL_PROP_TYPE_DOUBLE],
  },

  distance:{
    /*运动距离*/
    action:6,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT32,SET_TYPE.PROTOCOL_PROP_TYPE_VALUE],
  },

  sportingTime:{
    /*运动时长*/
    action:7,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT16,SET_TYPE.PROTOCOL_PROP_TYPE_DOUBLE],
  },

  burnCalories:{
    /*消耗热量*/
    action:8,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT16,SET_TYPE.PROTOCOL_PROP_TYPE_DOUBLE]
  },

  heartRate:{
    /*心率*/
    action:9,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM]
  },

  errorCode:{
    /*错误码*/
    action:10,
    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
    swap:{//mcu属性值与天猫精灵属性值的映射关系
      0:149,
      1:162,
      2:163,
      3:164,
      4:165,
    }, 
  },
   workSwitch:{
    /*工作状态控制*/
    action:11,
	    protocolType:[POST_TYPE.PROTOCOL_PROP_TYPE_UINT8,SET_TYPE.PROTOCOL_PROP_TYPE_ENUM],
	    swap:{//前面是协议中的参数  后面对应的是平台上的参数
        0:0,//关闭
	      1:1,//打开
	      2:2,//待机
	    },
	  }

  

};

var g_serviceArray = [];
var g_serviceDataMap = {
};

var g_eventArray = [];
var g_eventDataMap = {
};

var g_structDataMap = {

};

//json转透传指令
function protocolToRawData(json)
{
    log('------------------------  protocolToRawData  start  ------------------------');
    var  params  =  json['params'];
    var  method  =  json['method'];
    //var  id  =  json['id'];
    var  v,  string  =  '',  charList  =  '',  type  =  0, byteLength = 0;

    var  payloadArray  =  [];
    if  (method  ==  THING_ATTRIBUTE_GET)//未用到
    {
        payloadArray.push(THING_ATTRIBUTE_GET_CMD);                         //  GET  BYTE  ->  0x01
        //payloadArray  =  payloadArray.concat(buffer_uint32(id));   //  ID  UINT32  ->  id
        for  (var  i  =  0;  i  <  params.length;  i++)  {
          action  =  g_attrTypeMap[params[i]].action;
            payloadArray.push(action);
            log(params[i]  +  "  "  +  action);
        }
    }
    else  if  (method  ==  THING_ATTRIBUTE_SET)//属性设置
    {
        //var byteLength = 0;
        for  (var  key  in  params)
        {
            // targetSpeed 先把 value * 10
            if(key=="targetSpeed"){
              params[key] = 10 * params[key];
            }
            
            var type  =  g_attrTypeMap[key].protocolType[1];
            var action  =  g_attrTypeMap[key].action;
            v = buffer_dynamic(params[key], type);
            if(g_attrTypeMap[key].hasOwnProperty('swap')){//定义的属性中含有swap的会进入这里
              var _swap = swap_swap(g_attrTypeMap[key].swap);//详细的对应关系
              v = _swap[params[key]];//进行数据交互
            }
            log(key + " : " + typeof(params[key]) + " " + params[key] + " after swap: " + v);
            // log(type + " " + action + " 0x" + v.toString('hex'),'lenght:'+v.length);
            // log("action",action);
            log("v",v)
            if(action==11){//调节模式
              switch (parseInt(v)){
                case 0 : v = 2;
                  break;
                case 2 : v = 3;
                  break;
                default: v = 1;
              } 
            }
            if(action==1){//调节模式
              switch (parseInt(v)){
                case 1 : v = 7;
                  break;
                case 2 : v = 9;
                  break;
                default: v = 8;
              } 
            }
            if(action==2){//减震功能
              switch (parseInt(v)){
                case 1 : v = 10;
                  break;
                case 2 : v = 11;
                  break;
                case 3 : v = 12;
                  break;
                default: v = 13;
              } 
            }
            if(action!=0){//因客户特殊的协议而加
              action=0;
            }
            payloadArray.push(action);//向数组里填充action
            payloadArray.push(action);//因客户特殊的协议添加0
            if(key=="targetSpeed"){
              payloadArray.push(6);//因客户特殊的协议添加0
              byteLength = 4;//数据长度
            }else{
              byteLength = 3;//数据长度
            }
            payloadArray = payloadArray.concat(v);//向数组里填充真实数据
        }
        // payloadArray = buffer_uint16(byteLength).concat(payloadArray)
    }
    else if (method == THING_SERVICE_INVOKE)//服务下发
    {
        var serviceName = json['serviceName'];
        var inputData = params;
        var serviceItem = g_serviceDataMap[serviceName];
        var inputArray = serviceItem.inputArray;
        for (var key in serviceItem.inputArray)//这里对友奥空调来说没必要，如果要通用需要重写
        {
            var inputparamName = inputArray[key];
            type = serviceItem.inputData[inputparamName].protocolType[0];
            action = serviceItem.action;
            var v = buffer_dynamic(inputData[inputparamName], type);
            // log(key + " : " + v + " " + params[key]);
            // log(type + " " + " 0x" + v.toString('hex'));
            payloadArray = payloadArray.concat(buffer_uint16(4+v.length));//4是 action、数据类型、功能长度 所占字节
            payloadArray.push(action);
            payloadArray.push(type);
            payloadArray = payloadArray.concat(buffer_uint16(v.length));
            payloadArray = payloadArray.concat(v);
        }
    }
    else
    {
        //do nothing
        return;
    }

    var retBuffer = new Uint8Array(byteLength);  //初始一个长度为1(tid)+byteLength(数据)的Uint8Array数组
    var dv = new DataView(retBuffer.buffer, 0);  
    //dv.setUint8(0,buffer_uint8(id)); //tid设置为数组的第一个元素

    for (var i = 0; i < payloadArray.length; i++) 
    {
        retBuffer[i] = parseInt(payloadArray[i]);
    }

    // var dataString = "";
    // for (var i = 0; i < retBuffer.length; i++) {
    //   dataString += "0x" + retBuffer[i].toString(16).padStart(2,'0')+" ";
    // }
    //log("return rawdata " + dataString);

    log('------------------------ protocolToRawData end ------------------------');
    return [].slice.call(retBuffer);
}

//透传指令转json
function rawDataToProtocol(bytes)
{
    log('------------------------ rawDataToProtocol start ------------------------');
    //获取上报的id,并分离出id
    //var c_id = bytes.shift();
    //协议补齐一位
    bytes.splice(6,0,"0")
    //转换为无符号的数组，注意Uint8Array不能直接操作，需要DataView来操作，请见下方
    var buffer;
    bytes.length += 1;
    //给数组赋值
    //log("bytes.length",bytes.length)
    if (bytes.length >= 16)
    {
      buffer = new Uint8Array(bytes.length);
      for (var i = 0; i < bytes.length; i++)
      {
          buffer[i] = bytes[i] & 0xff;
      }
    }
    else {
      buffer = new Uint8Array(17);
      //解压缩
      buffer[0]  = bytes[0] & 0xff;
      buffer[1]  = (bytes[1] >> 6) & 0x03;
      buffer[2]  = (bytes[1] >> 3) & 0x07;
      buffer[4]  = (bytes[1] >> 0) & 0x07;

      buffer[3]  = (bytes[2] >> 6) & 0x01;
      buffer[5]  = (bytes[2] >> 5) & 0x01;
      buffer[6]  = (bytes[2] >> 4) & 0x01;
      buffer[14] = (bytes[2] >> 2) & 0x03;

      buffer[15] = bytes[10] & 0xff;
      buffer[16] = bytes[11] & 0xff;

      for (var i = 0; i < 7; i++)
      {
          buffer[7+i] = bytes[3+i] & 0xff;
      }

    }

    var dv = new DataView(buffer.buffer, 0);
    //log("dv",dv)
    //decode payload
    /*
    var dataString = ""
    for (var i = 0; i < buffer.length; i++) {
      dataString += "0x" + buffer[i].toString(16).padStart(2,'0')+" ";
    }
    log("return rawdata " + dataString);
    */
    var jsonMap = new Object();

    var params = {
      //errorCode:149
    };
    jsonMap['method'] = THING_ATTRIBUTE_POST;
    var offset = 0;
    var size = bytes.length;
    var count = 0;
    while (size >= offset && count <= 11) {
      if (true)
      {
        var payloadObj = type_dynamic(dv,count,offset);
        params[payloadObj.attribute] = payloadObj.value;
        
         if(count==3){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = payloadObj.value/10;
        }
        
        if(count==4){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = payloadObj.value/10;
        }

        if(count==5){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = payloadObj.value;
          offset++;
        }
        if(count==6){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = payloadObj.value * 10; // 运动距离，设备上报单位为 10 米
          offset=offset+3;
        }
        if(count==7){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = parseInt(payloadObj.value / 60); // 运动时间, 设备上报单位为 秒， 要转为分
          offset++;
        }
        if(count==8){
          var payloadObj = type_dynamic(dv,count,offset);
          params[payloadObj.attribute] = payloadObj.value / 10; // 消耗卡路里，设备上报单位是 0.1 千卡
          offset++;
        }
      }
      offset++;
      count++;
    }

    // var payloadObj = type_dynamic(dv,0,0);
    // var a = payloadObj.value; 
    // var b = parseInt(a);
    var b = parseInt(type_dynamic(dv,0,0).value);
    var workSwitch_t;
    switch (b){
      case 0:
        workSwitch_t = 0;
        break;
      case 1:
        workSwitch_t = 1;
        break;
      case 2:
        workSwitch_t = 2;
        break;
      case 3:
        workSwitch_t = 1;
        break;
      case 37:
        workSwitch_t = 1;
        break;
    }
    var payloadObj = type_dynamic(dv,11,11);
    params[payloadObj.attribute] = workSwitch_t; // 开关

    jsonMap['params'] = params;
    //jsonMap['id'] = '' + c_id;
    jsonMap['version'] = VERSION;
    log("jsonMap",jsonMap)
    //log("finished: " + JSON.stringify(jsonMap));
    log('------------------------ rawDataToProtocol end ------------------------');
  	return jsonMap;
}

function transformPayload(topic, rawData) {
  var jsonObj = {}
  return jsonObj;
}

function log(){
    try{
        console.log.apply(console, arguments);
    } catch (e){

    }
    try{
        print.apply(print, arguments);
    } catch (e){

    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
function type_uint8(dv, offset) { return {"value":dv.getUint8(offset), "length":1};}
function type_int8(dv, offset) { return {"value":dv.getInt8(offset), "length":1};}
function type_uint16(dv, offset) { return {"value":dv.getUint16(offset), "length":2};}
function type_int16(dv, offset) { return {"value":dv.getInt16(offset), "length":2};}
function type_int32(dv, offset) { return {"value":dv.getInt32(offset), "length":4};}
function type_uint32(dv, offset) { return {"value":dv.getUint32(offset), "length":4};}
function type_int64(dv, offset)
{
  var low = dv.getUint32(offset + 4);
  var n = dv.getUint32(offset) * 4294967296.0 + low;
  if (low < 0) n += 4294967296;
  return {"value":n, "length":8};
}
function type_uint64(dv, offset)
{
  var low = dv.getUint32(offset + 4);
  var n = dv.getUint32(offset) * 4294967296.0 + low;
  if (low < 0) n += 4294967296;
  return {"value":n, "length":8};
}

function type_float(dv, offset) 
{
	 return {"value":dv.getFloat32(offset), "length":4};
}
function type_double(dv, offset) 
{
	 return {"value":dv.getFloat64(offset), "length":8};
}
function type_string(bytes, offset, length)
{
	var value = String.fromCharCode.apply(null, bytes.subarray(offset, offset + length));
	var endIndex = value.indexOf('\u0000', 0);
	if (endIndex >= 0)
	  value = value.substr(0, endIndex);

	return {"value":value, "length":length};
}

// [typeID -> byte] [attrID -> byte] [value -> dynamic]
// [typeID -> byte] [attrID -> byte] [length -> int16] [value -> dynamic]

function type_dynamic_with_param(bytes, typeID, tmpOffset)
{
    var value = null, v = 0;
	if (typeID == POST_TYPE.PROTOCOL_PROP_TYPE_BOOL)
	{
		v = type_uint8(bytes, tmpOffset);
		value = v.value;
	}
	else if (typeID == POST_TYPE.PROTOCOL_PROP_TYPE_INT8)
	{
		v = type_int8(bytes, tmpOffset);
		value = v.value;
	}
	else if (typeID == POST_TYPE.PROTOCOL_PROP_TYPE_UINT8)
	{
		v = type_uint8(bytes, tmpOffset);
		value = v.value;
	}
	else if (typeID == POST_TYPE.PROTOCOL_PROP_TYPE_UINT16)
	{
		v = type_uint16(bytes, tmpOffset);
		value = v.value;
  }
  else if (typeID == POST_TYPE.PROTOCOL_PROP_TYPE_UINT32)
	{
		v = type_uint32(bytes, tmpOffset);
		value = v.value;
	}
	return {"value":value, "length":v.length};
}

function action_swap(map){
  var _swap = {}
  for(var key in map){
    _swap[map[key].action] = key
  }
  return _swap
}

function swap_swap(map){
  var _swap = {}
  for(var key in map){
    _swap[map[key]] = key
  }
  //log(_swap);
  return _swap
}

function type_dynamic(dv,action,tmpOffset)
{
  var _attr_swap = action_swap(g_attrTypeMap);
  var attribute = _attr_swap[action];
  var typeID = g_attrTypeMap[attribute].protocolType[0];

  var v = type_dynamic_with_param(dv, typeID, tmpOffset);
  
  var value = v.value;
  if(g_attrTypeMap[attribute].hasOwnProperty('swap')){
    value = g_attrTypeMap[attribute].swap[value]
  }
	return {"value":value, "length":v.length, attribute:attribute};
}

function buffer_uint8(value)
{
    var uint8Array = new Uint8Array(1);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setUint8(0, value);
    return [].slice.call(uint8Array);
}
function buffer_int8(value)
{
    var uint8Array = new Uint8Array(1);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setInt8(0, value);
    return [].slice.call(uint8Array);
}
function buffer_int16(value)
{
    var uint8Array = new Uint8Array(2);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setInt16(0, value);
    return [].slice.call(uint8Array);
}
function buffer_uint16(value)
{
    var uint8Array = new Uint8Array(2);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setUint16(0, value);
    return [].slice.call(uint8Array);
}
function buffer_uint32(value)
{
    var uint8Array = new Uint8Array(4);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setUint32(0, value);
    return [].slice.call(uint8Array);
}
function buffer_int32(value)
{
    var uint8Array = new Uint8Array(4);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setInt32(0, value);
    return [].slice.call(uint8Array);
}
function buffer_int64(value)
{
    //Number.MAX_SAFE_INTEGER
    var local_MAX_UINT32 = 0xFFFFFFFF;
    var big = ~~(value / local_MAX_UINT32);
    var low = (value % local_MAX_UINT32) - big;
    var uint8Array = new Uint8Array(8);
    var dv = new DataView(uint8Array.buffer, 0);
	  dv.setInt32(0, big);
	  dv.setInt32(4, low);
    return [].slice.call(uint8Array);
}
function buffer_uint64(value)
{
    //Number.MAX_SAFE_INTEGER
    var local_MAX_UINT32 = 0xFFFFFFFF;
    var big = ~~(value / local_MAX_UINT32);
    var low = (value % local_MAX_UINT32) - big;
    var uint8Array = new Uint8Array(8);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setUint32(0, big);
    dv.setUint32(4, low);
    return [].slice.call(uint8Array);
}
function buffer_float(value)
{
    var uint8Array = new Uint8Array(4);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setFloat32(0, value);
    return [].slice.call(uint8Array);
}
function buffer_double(value)
{
    var uint8Array = new Uint8Array(8);
    var dv = new DataView(uint8Array.buffer, 0);
    dv.setFloat64(0, value);
    return [].slice.call(uint8Array);
}
function buffer_string(value)
{
    var string = unescape(encodeURIComponent(value));
    var charList = string.split('');
    var uint8Array = new Array();
    for (var i = 0; i < charList.length; i++) {
        uint8Array.push(charList[i].charCodeAt(0));
    }
    var byteLength = uint8Array.length;
    return [].concat(buffer_int16(byteLength), uint8Array);
}

function buffer_dynamic(value, typeID)
{
  switch(typeID){
    case SET_TYPE.PROTOCOL_PROP_TYPE_BOOL:
      return buffer_uint8(value);
      break;
    case SET_TYPE.PROTOCOL_PROP_TYPE_VALUE:
      return buffer_int32(value);
      break;
    case SET_TYPE.PROTOCOL_PROP_TYPE_DOUBLE:
      return buffer_int16(value);
      break;
    case SET_TYPE.PROTOCOL_PROP_TYPE_ENUM:
    case SET_TYPE.PROTOCOL_PROP_TYPE_FAULT:
      return buffer_uint8(value);
      break;
  }
}