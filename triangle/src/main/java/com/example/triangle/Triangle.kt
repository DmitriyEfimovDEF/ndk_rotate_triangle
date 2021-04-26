package com.example.triangle

import android.util.Log
import androidx.annotation.Keep

class Triangle /*: OnRadSetListener*/{
//
//    init {
//        Log.d("~~~~"," triangle created")
//    }
    var listeners = mutableListOf<OnRadSetListener>()

    external fun draw(width: Float, height: Float, scale: Float, angle: Float)
    external fun onRadSet(rad: Float)

    @Keep
    private fun updateRad(str: String){
        Log.d("~~~~~ handler", str)
    }
/*    override fun onRadSetCall(rad: Float){
        repeat(listeners.size) {
            Log.d("~~~~"," rad value is $rad")

            this.onRadSet(rad)
        }
    }*/
    companion object {
        init {
            System.loadLibrary("Triangle")
        }
    }
}

interface OnRadSetListener {

    fun onRadSetCall(rad: Float)
}