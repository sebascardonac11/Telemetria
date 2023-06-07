import React, {useState} from 'react';
import {Text, View, TextInput, StyleSheet, Button, Alert} from 'react-native';

export default function Login() {
  const [dataForm, setDataForm] = useState({email: '', pass: ''});

  const login = () => {
    alert('INGRESE 2 ' + dataForm.email + ' ' + dataForm.pass);
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
      <Button title="Ingresar" onPress={login}></Button>
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
