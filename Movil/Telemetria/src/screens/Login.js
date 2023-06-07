import React, {useState} from 'react';
import {Text, View, TextInput, StyleSheet, Button, Alert} from 'react-native';
import AsyncStorage from '@react-native-async-storage/async-storage';
import {CognitoUser, AuthenticationDetails} from 'amazon-cognito-identity-js';

import {cognitoPool} from '../utils/cognito-pool';

export default function Login() {
  const [dataForm, setDataForm] = useState({email: '', pass: ''});
  //const [user, setUser] = useState({});

  const onPressLogin = () => {
    const user = new CognitoUser({
      Username: dataForm.email,
      Pool: cognitoPool,
    });
    //setUser(user);
    const authDetails = new AuthenticationDetails({
      Username: dataForm.email,
      Password: dataForm.pass,
    });
    user.authenticateUser(authDetails, {
      onSuccess: async res => {
        const token = res?.refreshToken?.token;
        await AsyncStorage.setItem('REFRESH_TOKEN', token);

        setTimeout(() => {
          navigation.navigate('main');
        }, 350);
      },
      onFailure: err => {
        switch (err.name) {
          case 'UserNotConfirmedException':
            return alert(err.name);
          case 'NotAuthorizedException':
            return alert(err.name);
          default:
            return alert(err);
        }
      },
    });
  };

  /*PARA REGISTRAR PERSONAS */
  const onPressRegister = () => {
    cognitoPool.signUp(
      'juliancc9226@gmail.com',
      'consentida22',
      [],
      null,
      (err, data) => {
        console.log('Err', err);
        console.log('Data ', data);
        if (err) {
          switch (err.name) {
            case 'InvalidParameterException':
              return alert('error ' + err.message);
            case 'InvalidPasswordException':
              return alert('error ' + err.message);
            case 'UsernameExistsException':
              return alert('error ' + err.message);
            default:
              return alert('error ' + err.message);
          }
        }
        Alert.alert(General.Success, Auth.ConfirmEmail, [
          {text: 'OK', onPress: () => navigation.navigate('login')},
        ]);
      },
    );
  };

  return (
    <View>
      <Text style={styles.labels}>Usuario</Text>
      <TextInput
        placeholder="Email"
        style={styles.inputEmail}
        autoCapitalize="none"
        value={dataForm.email}
        onChangeText={text => {
          var newDataForm = {...dataForm};
          newDataForm.email = text;
          setDataForm(newDataForm);
        }}
        keyboardType="email-address"
      />
      <Text style={styles.labels}>Contraseña</Text>
      <TextInput
        placeholder="Contraseña"
        style={styles.inputEmail}
        autoCapitalize="none"
        secureTextEntry={true}
        value={dataForm.pass}
        onChangeText={text => {
          var newDataForm = {...dataForm};
          newDataForm.pass = text;
          setDataForm(newDataForm);
        }}
      />
      <Button title="Ingresar" onPress={onPressLogin}></Button>
      <Button title="Registrar" onPress={onPressRegister}></Button>
    </View>
  );
}

const styles = StyleSheet.create({
  labels: {
    color: 'black',
  },
  inputEmail: {
    color: 'red',
  },
});
