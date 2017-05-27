#!/usr/bin/env groovy

def projDirMap = [
	'diagnostic' : 'examples/diagnostic',
	'externalInterrupt' : 'examples/externalInterrupt',
	'gpio' : 'examples/gpio',
	'os' : 'examples/os',
	'serialPort' : 'examples/serialPort',
	'signal slot' : 'examples/signalSlot',
	'ticToc' : 'examples/ticToc',
	'cli' : 'components/cli/examples/cli',
	'hostComm' : 'components/hostComm/examples/simpeCommunication',
	'at45db' : 'drivers/Atmel/AT45DB041D/example',        
	'bmp180' : 'drivers/Bosch/BMP180/example/basic',
	'ds2782' : 'drivers/MaximDallas/DS2782/example/basic',
	'ds2786' : 'drivers/MaximDallas/DS2786/example/basic',        
	'hx711' : 'drivers/AVIA Semiconductor/HX711/example',
	'isl29023' : 'drivers/Intersil/ISL29023/example/basic',        
	'leptonPCSerialReceiver' : 'drivers/FLIR/Lepton/example/lepton_PC_Serial_Receiver',
	'leptonSDCardWrite' : 'drivers/FLIR/Lepton/example/lepton_SDCard_write',
	'leptonSerialTransmitter' : 'drivers/FLIR/Lepton/example/lepton_Serial_Transmitter',
	'lis302' : 'drivers/STMicroelectronics/LIS302/example/lis302',
	'lsm330dl' : 'drivers/STMicroelectronics/LSM330DL/example/basic',
	'm24c16' : 'drivers/STMicroelectronics/M24C16/example',
	'mcp9800' : 'drivers/Microchip/MCP9800/example',
	'mpl115a1' : 'drivers/Freescale Semiconductor/MPL115A1/example',
	'mpl115a2' : 'drivers/Freescale Semiconductor/MPL115A2/example',
	'mrf89xa' : 'drivers/Microchip/MRF89XA/example/mrf89xa',
	'pcf8563' : 'drivers/NXP/PCF8563/example',
	'rfm70' : 'drivers/Hoperf Electronic/RFM70/example/packet_send',
	'sht21' : 'drivers/Sensirion/SHT21/example/basic',
	'tmp006' : 'drivers/Texas Instruments/TMP006/example/temperature_show',
	'uCAM-II' : 'drivers/4D Systems/uCAM-II/example',
	'ws2812' : 'drivers/Worldsemi/WS2812/example',
	'serialPort_test' : 'tests/serialPort',
	'stm32f3xx_allMCU' : 'tests/stm32f3xx_AllMCU',
	'stm32f4xx_allMCU' : 'tests/stm32f4xx_AllMCU',
        'stm32f4xx_stat_serialPort' : 'tests/statistics/stm32f4xx/serialPort',
]

def eclipseRun(project, target, defines) {
    def workspace = 'workspace_' + project.replaceAll("\\s","_")    
    def defs = ''
    for (define in defines) {
        defs = defs + ' -D ' + define
    }	    
    if (env.NODE_NAME == 'master') {
        lock(label: 'master_core', quantity: 1) {
             withEnv(['PATH+WHATEVER=/srv/jenkins/tools/microide:/srv/jenkins/tools/microide/toolchains/arm-none-eabi-gcc/microhal/gcc-arm-none-eabi-5_3-2016q1/bin']) {
                retry(2) {
                    timeout(time:10, unit:'MINUTES') {			
                        sh 'eclipse -configuration /srv/jenkins --launcher.suppressErrors -nosplash -no-indexer' + defs + ' -data ' + workspace + ' -import "' + project + '" -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild "' + target + '"'
                    }
                }  
            }	
        }
    }
    if (env.NODE_NAME == 'FX160_HardwareTester') {
        lock(label: 'hwTester_core', quantity: 1) {
            withEnv(['PATH+WHATEVER=/var/jenkins/tools/microide/toolchains/gcc-arm-none-eabi/microhal/gcc-arm-none-eabi-5_3-2016q1/bin:/var/jenkins/tools/microide/eclipse']) {
                retry(2) {
                    timeout(time:10, unit:'MINUTES') {
                        sh 'eclipse --launcher.suppressErrors -nosplash -no-indexer' + defs + ' -data ' + workspace + ' -import "' + project + '" -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild "' + target + '"'                        
                    }
                }
            }
        }
    }
}

def eclipseBuild(projName, targets) {     
	def projDirMap = [
	'diagnostic' : 'examples/diagnostic',
	'externalInterrupt' : 'examples/externalInterrupt',
	'gpio' : 'examples/gpio',
	'os' : 'examples/os',
	'serialPort' : 'examples/serialPort',
	'signal slot' : 'examples/signalSlot',
	'ticToc' : 'examples/ticToc',
	'cli' : 'components/cli/examples/cli',
	'hostComm' : 'components/hostComm/examples/simpeCommunication',
	'at45db' : 'drivers/Atmel/AT45DB041D/example',        
	'bmp180' : 'drivers/Bosch/BMP180/example/basic',
	'ds2782' : 'drivers/MaximDallas/DS2782/example/basic',
	'ds2786' : 'drivers/MaximDallas/DS2786/example/basic',        
	'hx711' : 'drivers/AVIA Semiconductor/HX711/example',
	'isl29023' : 'drivers/Intersil/ISL29023/example/basic',        
	'leptonPCSerialReceiver' : 'drivers/FLIR/Lepton/example/lepton_PC_Serial_Receiver',
	'leptonSDCardWrite' : 'drivers/FLIR/Lepton/example/lepton_SDCard_write',
	'leptonSerialTransmitter' : 'drivers/FLIR/Lepton/example/lepton_Serial_Transmitter',
	'lis302' : 'drivers/STMicroelectronics/LIS302/example/lis302',
	'lsm330dl' : 'drivers/STMicroelectronics/LSM330DL/example/basic',
	'm24c16' : 'drivers/STMicroelectronics/M24C16/example',
	'mcp9800' : 'drivers/Microchip/MCP9800/example',
	'mpl115a1' : 'drivers/Freescale Semiconductor/MPL115A1/example',
	'mpl115a2' : 'drivers/Freescale Semiconductor/MPL115A2/example',
	'mrf89xa' : 'drivers/Microchip/MRF89XA/example/mrf89xa',
	'pcf8563' : 'drivers/NXP/PCF8563/example',
	'rfm70' : 'drivers/Hoperf Electronic/RFM70/example/packet_send',
	'sht21' : 'drivers/Sensirion/SHT21/example/basic',
	'tmp006' : 'drivers/Texas Instruments/TMP006/example/temperature_show',
	'uCAM-II' : 'drivers/4D Systems/uCAM-II/example',
	'ws2812' : 'drivers/Worldsemi/WS2812/example',
	'serialPort_test' : 'tests/serialPort',
	'stm32f3xx_allMCU' : 'tests/stm32f3xx_AllMCU',
	'stm32f4xx_allMCU' : 'tests/stm32f4xx_AllMCU',
]
    echo "Building on ${env.NODE_NAME}"
    for (target in targets) {
        def buildTarget = projName + '/' + target
	if (target == 'all') {
	    buildTarget = 'all'
        }
        eclipseRun(projDirMap[projName], buildTarget, [])
    }	
}

def sa(projName, targets) {
    def projDirMap = [
        'diagnostic' : 'examples/diagnostic',
        'externalInterrupt' : 'examples/externalInterrupt',
        'gpio' : 'examples/gpio',
        'os' : 'examples/os',
        'serialPort' : 'examples/serialPort',
        'signal slot' : 'examples/signalSlot',
        'ticToc' : 'examples/ticToc',
        'cli' : 'components/cli/examples/cli',
        'hostComm' : 'components/hostComm/examples/simpeCommunication',
        'at45db' : 'drivers/Atmel/AT45DB041D/example',        
        'bmp180' : 'drivers/Bosch/BMP180/example/basic',
        'ds2782' : 'drivers/MaximDallas/DS2782/example/basic',
        'ds2786' : 'drivers/MaximDallas/DS2786/example/basic',        
        'hx711' : 'drivers/AVIA Semiconductor/HX711/example',
        'isl29023' : 'drivers/Intersil/ISL29023/example/basic',        
        'leptonPCSerialReceiver' : 'drivers/FLIR/Lepton/example/lepton_PC_Serial_Receiver',
        'leptonSDCardWrite' : 'drivers/FLIR/Lepton/example/lepton_SDCard_write',
        'leptonSerialTransmitter' : 'drivers/FLIR/Lepton/example/lepton_Serial_Transmitter',
        'lis302' : 'drivers/STMicroelectronics/LIS302/example/lis302',
        'lsm330dl' : 'drivers/STMicroelectronics/LSM330DL/example/basic',
        'm24c16' : 'drivers/STMicroelectronics/M24C16/example',
	'mcp9800' : 'drivers/Microchip/MCP9800/example',
        'mpl115a1' : 'drivers/Freescale Semiconductor/MPL115A1/example',
        'mpl115a2' : 'drivers/Freescale Semiconductor/MPL115A2/example',
        'mrf89xa' : 'drivers/Microchip/MRF89XA/example/mrf89xa',
        'pcf8563' : 'drivers/NXP/PCF8563/example',
        'rfm70' : 'drivers/Hoperf Electronic/RFM70/example/packet_send',
        'sht21' : 'drivers/Sensirion/SHT21/example/basic',
        'tmp006' : 'drivers/Texas Instruments/TMP006/example/temperature_show',
        'uCAM-II' : 'drivers/4D Systems/uCAM-II/example',
        'ws2812' : 'drivers/Worldsemi/WS2812/example',
        'serialPort_test' : 'tests/serialPort',
	'stm32f3xx_allMCU' : 'tests/stm32f3xx_AllMCU',
    ]
     
    lock(label: 'hwTester_core', quantity: 1) {
        withEnv(['PATH+WHATEVER=/var/jenkins/tools/microide/toolchains/gcc-arm-none-eabi/microhal/gcc-arm-none-eabi-5_3-2016q1/bin:/var/jenkins/tools/microide/eclipse']) {
            for (target in targets) {               
                timeout(time:10, unit:'MINUTES') {
                    sh '''#!/bin/bash
                    echo -target arm-none-eabi > extra_clang_options
                    echo -/third-party* > skipfile
                    source /var/jenkins/tools/codechecker/venv/bin/activate 
                    export PATH=/var/jenkins/tools/codechecker/build/CodeChecker/bin:$PATH 
                    export PATH=/var/jenkins/tools/microide/toolchains/gcc-arm-none-eabi/microhal/gcc-arm-none-eabi-5_3-2016q1/bin:$PATH
                    CodeChecker check --saargs extra_clang_options --skip skipfile -j 2 -e alpha -e llvm -n ''' + projName.replaceAll("\\s","_") + '_' + target + ' -b "cd ' + projDirMap[projName] + '/' + target +' && make clean && make all"'                    
                }        
            }
        }
    }
}

def targets = ['stm32f4-discovery', 'NUCLEO-F411RE', 'NUCLEO-F334R8']
pipeline {   
    agent {
        node {
            label 'master'
        }    
    }   

    stages {
        stage('Checkout') {
            steps {
               	checkout scm
                sh 'git submodule update --init'               
            }
        }
        stage('Build microhal examples') {
            steps {
                parallel(
                    diagnostic :        { eclipseBuild('diagnostic', ['stm32f4-discovery', 'NUCLEO-F411RE', 'NUCLEO-F334R8', 'linux']) },
                    externalInterrupt : { eclipseBuild('externalInterrupt', targets) },
                    gpio :              { eclipseBuild('gpio', targets) },
                    os :                { eclipseBuild('os', targets) },
                    serialPort :        { eclipseBuild('serialPort', targets) },
                    signalSlot :        { eclipseBuild('signal slot', ['stm32f4-discovery', 'NUCLEO-F411RE', 'NUCLEO-F334R8', 'linux']) },
                    ticToc :            { eclipseBuild('ticToc', ['stm32f4-discovery', 'NUCLEO-F411RE', 'NUCLEO-F334R8', 'linux']) },
                )
            }
        }
        stage('Build components examples') {
            steps {
                parallel(
                    cli : { eclipseBuild('cli', ['stm32f4-discovery']) },
                    hostComm : { eclipseBuild('hostComm', ['stm32f4-discovery']) }
                )
            }
        }
        stage('Build devices examples') {
            steps {
                parallel(
                    at45db : { eclipseBuild('at45db', targets) },
                    bmp180 : { eclipseBuild('bmp180', targets) },
                    ds2782 : { eclipseBuild('ds2782', targets) },
                    ds2786 : { eclipseBuild('ds2786', targets) },
                    hx711 : { eclipseBuild('hx711', targets) },
                    isl29023 : { eclipseBuild('isl29023', targets) },
                    lepton : { eclipseBuild('leptonPCSerialReceiver', ['reader linux'])
                               eclipseBuild('leptonSDCardWrite', ['stm32f4-discovery'])
                               eclipseBuild('leptonSerialTransmitter', ['stm32f4-discovery']) },
                    lis302 : { eclipseBuild('lis302', targets) },
                    lsm330dl : { eclipseBuild('lsm330dl', targets) },
                    m24c16 : { eclipseBuild('m24c16', targets) },
                    mcp9800 : { eclipseBuild('mcp9800', ['stm32f4-discovery']) },		    
                    mpl115a2 : { eclipseBuild('mpl115a2', targets) },
                    mrf89xa : { eclipseBuild('mrf89xa', targets) },
                    pcf8563 : { eclipseBuild('pcf8563', targets) },
                    rfm70 : { eclipseBuild('rfm70', targets) },
                    sht21 : { eclipseBuild('sht21', targets) },
                    tmp006 : { eclipseBuild('tmp006', targets) },
                    uCamII : { eclipseBuild('uCAM-II', ['stm32f4-discovery']) },
                    ws2812 : { eclipseBuild('ws2812', targets) },                    
                )
            }
        }
        stage('Test - build all targets') {
            steps {
		parallel(
			stm32f3xx : { eclipseBuild('stm32f3xx_allMCU', ['all']) },
			STM32F405xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F405xx']) },
			STM32F415xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F415xx']) },
			STM32F407xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F407xx']) },
			STM32F417xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F417xx']) },
			STM32F427xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F427xx']) },
			STM32F437xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F437xx']) },
			STM32F429xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F429xx']) },
			STM32F439xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F439xx']) },
			STM32F401xC : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F401xC']) },
			STM32F401xE : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F401xE']) },
			STM32F410Tx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F410Tx']) },
			STM32F410Cx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F410Cx']) },
			STM32F410Rx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F410Rx']) },
			STM32F411xE : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F411xE']) },
			STM32F446xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F446xx']) },
			STM32F469xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F469xx']) },
			STM32F479xx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F479xx']) },
			STM32F412Cx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F412Cx']) },
			STM32F412Zx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F412Zx']) },
			STM32F412Vx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F412Vx']) },
			STM32F412Rx : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/interrupt', ['STM32F412Rx']) },		
			STM32F405xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F405xx']) },
			STM32F415xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F415xx']) },
			STM32F407xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F407xx']) },
			STM32F417xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F417xx']) },
			STM32F427xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F427xx']) },
			STM32F437xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F437xx']) },
			STM32F429xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F429xx']) },
			STM32F439xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F439xx']) },
			STM32F401xCp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F401xC']) },
			STM32F401xEp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F401xE']) },
			STM32F410Txp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F410Tx']) },
			STM32F410Cxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F410Cx']) },
			STM32F410Rxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F410Rx']) },
			STM32F411xEp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F411xE']) },
			STM32F446xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F446xx']) },
			STM32F469xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F469xx']) },
			STM32F479xxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F479xx']) },
			STM32F412Cxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F412Cx']) },
			STM32F412Zxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F412Zx']) },
			STM32F412Vxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F412Vx']) },
			STM32F412Rxp : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/polling', ['STM32F412Rx']) },
			STM32F405xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F405xx']) },
			STM32F415xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F415xx']) },
			STM32F407xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F407xx']) },
			STM32F417xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F417xx']) },
			STM32F427xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F427xx']) },
			STM32F437xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F437xx']) },
			STM32F429xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F429xx']) },
			STM32F439xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F439xx']) },
			STM32F401xCd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F401xC']) },
			STM32F401xEd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F401xE']) },
			STM32F410Txd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F410Tx']) },
			STM32F410Cxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F410Cx']) },
			STM32F410Rxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F410Rx']) },
			STM32F411xEd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F411xE']) },
			STM32F446xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F446xx']) },
			STM32F469xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F469xx']) },
			STM32F479xxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F479xx']) },
			STM32F412Cxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F412Cx']) },
			STM32F412Zxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F412Zx']) },
			STM32F412Vxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F412Vx']) },
			STM32F412Rxd : { eclipseRun(projDirMap['stm32f4xx_allMCU'], 'stm32f4xx_allMCU/dma', ['STM32F412Rx']) },

		)		
            }
        }  
        stage('Test - code size statistics') {
	    steps {
                // serialPort code usage
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', [])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT4_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT4_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT5_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT4_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT5_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT6_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT4_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT5_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT6_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT7_INTERRUPT'])
                eclipseRun(projDirMap['stm32f4xx_stat_serialPort'], 'stm32f4xx_stat_serialPort/jenkins', ['MICROHAL_USE_SERIAL_PORT1_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT2_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT3_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT4_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT5_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT6_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT7_INTERRUPT', 'MICROHAL_USE_SERIAL_PORT8_INTERRUPT'])
            }	    
        }
        stage('Checkout tester') {
	    agent { 
                label 'FX160_HardwareTester'
            }
            steps {
                sh 'git submodule update --init'
//                unstash 'makefiles'		                
            }
	}
        stage('Build on tester') {
	    agent { 
                label 'FX160_HardwareTester'
            }
            steps {
                parallel(
                    diagnostic :        { eclipseBuild('diagnostic', targets) },
                    externalInterrupt : { eclipseBuild('externalInterrupt', targets) },
                    gpio :              { eclipseBuild('gpio', targets) },
                    os :                { eclipseBuild('os', targets) },
                    serialPort :        { eclipseBuild('serialPort', targets) },
                    signalSlot :        { eclipseBuild('signal slot', targets) },
                    ticToc :            { eclipseBuild('ticToc', targets) },
                )
            }
        }
	stage('Analyze microhal examples') {
	    agent { 
                label 'FX160_HardwareTester'
            }
	    steps {		
                parallel(
                    diagnostic :        { sa('diagnostic', targets) },
                    externalInterrupt : { sa('externalInterrupt', targets) },
                    gpio :              { sa('gpio', targets) },
                    os :                { sa('os', targets) },
                    serialPort :        { sa('serialPort', targets) },
                    signalSlot :        { sa('signal slot', targets) },
                    ticToc :            { sa('ticToc', targets) },
                )
            }	    
        }
        stage('Create documentation') {
            when {
                expression { env.BRANCH_NAME == 'master'}
            }
            steps {
                sh 'doxygen microhal/core/HAL_DOC.doxyfile'
            }
            post {
                success {
                    echo "Documentation is published."
                    // todo(pokas) publish documentation
                }
            }
        }	
    }
    post {
        always {
            deleteDir()
        }
    }
}

