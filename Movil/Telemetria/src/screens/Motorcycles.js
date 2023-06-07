import React, {useState, useEffect} from 'react';
import {FlatList, StyleSheet} from 'react-native';
import AsyncStorage from '@react-native-async-storage/async-storage';
import {CognitoUser, AuthenticationDetails} from 'amazon-cognito-identity-js';

import {cognitoPool} from '../utils/cognito-pool';

import MotorcycleCard from '../components/MotorcycleCard';
import {getMotorcyclesApi} from '../api/motorcyclesApi';

export default function Motorcycles() {
  const [motorcycles, setMotorcycles] = useState([]);
  console.log('renderizando');
  /* useEffect(() => {
    (async () => {
      await loadMotorcycles();
    })();
  }, []); */

  useEffect(() => {
    loadMotorcycles();
  }, []);

  const loadMotorcycles = async () => {
    try {
      const result = await getMotorcyclesApi();
      console.log('result ', result);
      setMotorcycles(result);
    } catch (error) {
      console.log('error getMotorcyclesApi ', error);
    }
  };

  //const [user, setUser] = useState({});

  return (
    <FlatList
      data={motorcycles}
      numColumns={2}
      showsVerticalScrollIndicator={false}
      keyExtractor={motorcycle => String(motorcycle.id)}
      renderItem={({item}) => <MotorcycleCard motorcycle={item} />}
      contentContainerStyle={styles.flatListContentContainer}
      onEndReachedThreshold={0.1}
    />
  );
}

const styles = StyleSheet.create({
  flatListContentContainer: {
    paddingHorizontal: 5,
    marginTop: Platform.OS === 'android' ? 30 : 0,
  },
  spinner: {
    marginTop: 20,
    marginBottom: Platform.OS === 'android' ? 90 : 60,
  },
});
