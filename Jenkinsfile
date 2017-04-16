def eclipseBuild(projName, target) {
    def projDirMap = [
        'at45db' : 'drivers/Atmel/AT45DB041D/example',
        'hx711' : 'drivers/AVIA Semiconductor/HX711/example',
        'bmp180' : 'drivers/Bosch/BMP180/example',
        'ds2782' : 'drivers/MaximDallas/DS2782/example'
    ]

    //sh '/home/microide/microide_build.sh --launcher.suppressErrors -nosplash -data workspace -importAll "' + projDirMap[projName] + '" -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild "' + projName + '/' + target + '"'
     withEnv(['PATH+WHATEVER=/var/jenkins/tools/microide/toolchains/gcc-arm-none-eabi/microhal/gcc-arm-none-eabi-5_3-2016q1/bin:/var/jenkins/tools/microide/eclipse']) {
         sh 'eclipse --launcher.suppressErrors -nosplash -data workspace -importAll "' + projDirMap[projName] + '" -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild "' + projName + '/' + target + '"'
     }
}

def buildAllDevExamples() {
    def projects = ['hx711', 'bmp180']
    def targets = ['stm32f4-discovery', 'NUCLEO-F411RE', 'NUCLEO-F334R8']
    for (project in projects) {
        for (target in targets) {
            eclipseBuild(project, target)
        }
    }
}

pipeline {   
    agent {
        node {
            label 'FX160_HardwareTester'           
        }    
    }   

    stages {
        stage('Prepare') {
            steps { 
                checkout scm
                sh 'git submodule update --init'
            }
        }
        stage('Build devices examples') {
            steps {                
               buildAllDevExamples()
            }
        }
        stage('Test') {
            steps {
                    echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }       
        }
    }
}
