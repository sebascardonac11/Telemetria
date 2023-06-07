import React, {useState} from 'react';
import {
  Text,
  View,
  StyleSheet,
  Image,
  TouchableWithoutFeedback,
} from 'react-native';

export default function MotorcycleCard(props) {
  const {motorcycle} = props;
  const selectMotorcycle = () => {
    console.log('motorcycle  ', motorcycle);
    alert(motorcycle.id);
  };
  return (
    <TouchableWithoutFeedback onPress={selectMotorcycle}>
      <View style={styles.card}>
        <View style={styles.bgStyles}>
          <Image
            source={{
              uri: motorcycle.imagen,
            }}
            style={styles.image}
          />
        </View>
        <Text style={styles.name}>{motorcycle.placa}</Text>
      </View>
    </TouchableWithoutFeedback>
  );
}

const styles = StyleSheet.create({
  card: {
    width: 100,
    height: 130,
    backgroundColor: 'rgba(20, 25, 55, 0.2)',
    //opacity: 0.5,
    margin: 10,
    borderRadius: 8,
  },
  bgStyles: {
    flex: 1,
    flexDirection: 'column',
    justifyContent: 'center',
  },
  name: {
    color: 'black',
    fontWeight: 'bold',
    fontSize: 15,
    alignSelf: 'center',
    paddingBottom: 6,
  },
  image: {
    alignSelf: 'center',
    width: 90,
    height: 90,
  },
});
