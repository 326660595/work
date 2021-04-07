const fs =  require('fs')
const path =  require('path')

const code = fs.readFileSync(path.join(__dirname,'index.js'),'utf-8')
eval(code)

// 下发控制
let json = {"method":"thing.attribute.set","params":{"workstatus":3},"id":"1","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"workstatus":37},"id":"2","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"workstatus":2},"id":"3","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"mode":346},"id":"4","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"mode":345},"id":"5","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"mode":347},"id":"6","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"shockAbsorbtionOnOff":1},"id":"7","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"shockAbsorbtionOnOff":2},"id":"8","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"shockAbsorbtionOnOff":3},"id":"9","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"shockAbsorbtionOnOff":4},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":10},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":20},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":30},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":40},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":50},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

json = {"method":"thing.attribute.set","params":{"speed":60},"id":"10","version":"1.0.0"};
BitConverter(protocolToRawData(json))

//模拟数据上报
let bytes = [0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
rawDataToProtocol(bytes);

// bytes = [0x2, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x3, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x4, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x5, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x6, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x7, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x8, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0x9, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0xa, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00];
// rawDataToProtocol(bytes);

// bytes = [0xb, 0x01, 0x00, 0x00, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x31, 0x02, 0x05, 0x00, 0x22, 0x00, 0x00];
// rawDataToProtocol(bytes);

function BitConverter(bytes){
    let str = ""
    for (const iterator of bytes) {
        if(str != "")
            str += " "
        str += iterator.toString(16).padStart(2,"0").toLocaleUpperCase()
    }
    console.log(str) ;
}